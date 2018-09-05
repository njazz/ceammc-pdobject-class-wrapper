#include "ceammc_preset.h"
#include "ceammc_format.h"
#include "ceammc_log.h"
#include "ceammc_platform.h"

extern "C" {
#include "g_canvas.h"
}

#include <boost/make_shared.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace ceammc {

static const size_t MAX_PRESET_COUNT = 16;
static t_symbol* SYM_WITH_SPACES = gensym("_symbol_s");

t_symbol* Preset::SYM_NONE = gensym("");
t_symbol* Preset::SYM_LOAD = gensym("load");
t_symbol* Preset::SYM_STORE = gensym("store");
t_symbol* Preset::SYM_UPDATE = gensym("update");
t_symbol* Preset::SYM_CLEAR = gensym("clear");
t_symbol* Preset::SYM_PRESET_ALL = gensym("preset update all");
t_symbol* PresetStorage::SYM_PRESET_UPDATE_INDEX_ADDR = gensym("preset index update addr");
t_symbol* PresetStorage::SYM_PRESET_INDEX_ADD = gensym("preset index add");
t_symbol* PresetStorage::SYM_PRESET_INDEX_REMOVE = gensym("preset index remove");

PresetStorage::PresetStorage()
    : indexes_(MAX_PRESET_COUNT, PresetNameSet())
{
}

PresetStorage& PresetStorage::instance()
{
    static PresetStorage instance_;
    return instance_;
}

size_t PresetStorage::maxPresetCount() const
{
    return MAX_PRESET_COUNT;
}

bool PresetStorage::setFloatValueAt(t_symbol* name, size_t presetIdx, float v)
{
    PresetPtr param = getOrCreate(name);
    addPresetIndex(name, presetIdx);
    return param->setFloatAt(presetIdx, v);
}

bool PresetStorage::clearValueAt(t_symbol* name, size_t presetIdx)
{
    PresetMap::iterator it = params_.find(name);
    if (it == params_.end())
        return false;

    removePresetIndex(name, presetIdx);
    return it->second->clearAt(presetIdx);
}

bool PresetStorage::setSymbolValueAt(t_symbol* name, size_t presetIdx, t_symbol* v)
{
    PresetPtr param = getOrCreate(name);
    addPresetIndex(name, presetIdx);
    return param->setSymbolAt(presetIdx, v);
}

t_symbol* PresetStorage::symbolValueAt(t_symbol* name, size_t presetIdx, t_symbol* def) const
{
    PresetMap::const_iterator it = params_.find(name);
    if (it == params_.end())
        return def;

    return it->second->symbolAt(presetIdx, def);
}

bool PresetStorage::setListValueAt(t_symbol* name, size_t presetIdx, const AtomList& l)
{
    PresetPtr param = getOrCreate(name);
    addPresetIndex(name, presetIdx);
    return param->setListAt(presetIdx, l);
}

AtomList PresetStorage::listValueAt(t_symbol* name, size_t presetIdx, const AtomList& def) const
{
    PresetMap::const_iterator it = params_.find(name);
    if (it == params_.end())
        return def;

    return it->second->listAt(presetIdx, def);
}

bool PresetStorage::setAnyValueAt(t_symbol* name, size_t presetIdx, t_symbol* sel, const AtomList& l)
{
    PresetPtr param = getOrCreate(name);
    addPresetIndex(name, presetIdx);
    return param->setAnyAt(presetIdx, sel, l);
}

AtomList PresetStorage::anyValueAt(t_symbol* name, size_t presetIdx, const AtomList& def) const
{
    PresetMap::const_iterator it = params_.find(name);
    if (it == params_.end())
        return def;

    return it->second->anyAt(presetIdx, def);
}

float PresetStorage::floatValueAt(t_symbol* name, size_t presetIdx, float def) const
{
    PresetMap::const_iterator it = params_.find(name);
    if (it == params_.end())
        return def;

    return it->second->floatAt(presetIdx, def);
}

bool PresetStorage::hasValueAt(t_symbol* name, size_t presetIdx) const
{
    PresetMap::const_iterator it = params_.find(name);
    if (it == params_.end())
        return false;

    return it->second->hasDataAt(presetIdx);
}

bool PresetStorage::hasValueTypeAt(t_symbol* name, Message::Type t, size_t presetIdx) const
{
    PresetMap::const_iterator it = params_.find(name);
    if (it == params_.end())
        return false;

    return it->second->hasDataTypeAt(presetIdx, t);
}

bool PresetStorage::hasFloatValueAt(t_symbol* name, size_t presetIdx)
{
    return hasValueTypeAt(name, Message::FLOAT, presetIdx);
}

static t_canvas* rootCanvas(t_canvas* cnv)
{
    if (!cnv)
        return 0;

    t_canvas* c = cnv;
    while (c->gl_owner)
        c = c->gl_owner;

    return c;
}

static std::string makePresetFilename(t_canvas* c, const std::string& path)
{
    if (path.empty()) {
        if (c)
            return platform::strip_extension(c->gl_name->s_name) + "-preset.txt";
        else
            return "";
    } else
        return path;
}

static std::string makeFullPresetPath(t_canvas* c, const std::string& name)
{
    if (!sys_isabsolutepath(name.c_str())) {
        if (c)
            return std::string(canvas_getdir(c)->s_name) + "/" + name;
        else
            return "./" + name;
    } else
        return name;
}

bool PresetStorage::write(t_canvas* c, const std::string& path) const
{
    t_canvas* root_cnv = rootCanvas(c);
    std::string name = makePresetFilename(root_cnv, path);
    std::string full_path = makeFullPresetPath(root_cnv, name);

    bool rc = write(full_path.c_str());
    if (!rc)
        LIB_ERR << "can't write presets to " << full_path;
    else
        LIB_DBG << "presets written to: " << full_path;

    return rc;
}

bool PresetStorage::write(const char* path) const
{
    if (params_.empty()) {
        LIB_DBG << "no presets in storage";
        return false;
    }

    t_binbuf* content = binbuf_new();

    PresetMap::const_iterator it;
    for (it = params_.begin(); it != params_.end(); ++it) {
        PresetPtr ptr = it->second;

        for (size_t i = 0; i < maxPresetCount(); i++) {
            if (!ptr->hasDataAt(i))
                continue;

            binbuf_addv(content, "sf", ptr->name(), double(i));

            if (ptr->hasFloatAt(i))
                binbuf_addv(content, "sf", &s_float, ptr->floatAt(i));
            else if (ptr->hasSymbolAt(i)) {
                t_symbol* sym = ptr->symbolAt(i);
                if (strchr(sym->s_name, ' ')) {
                    // has spaces
                    binbuf_addv(content, "ss", SYM_WITH_SPACES, sym);
                } else {
                    // no spaces
                    binbuf_addv(content, "ss", &s_symbol, sym);
                }
            } else if (ptr->hasListAt(i)) {
                AtomList l = ptr->listAt(i);
                binbuf_addv(content, "s", &s_list);
                binbuf_add(content, l.size(), l.toPdData());
            } else if (ptr->hasAnyAt(i)) {
                AtomList l = ptr->anyAt(i);
                binbuf_add(content, l.size(), l.toPdData());
            }

            binbuf_addsemi(content);
        }
    }

    int rc = binbuf_write(content, (char*)path, (char*)"", 0);
    binbuf_free(content);

    return rc == 0;
}

bool PresetStorage::read(t_canvas* c, const std::string& path)
{
    t_canvas* root_cnv = rootCanvas(c);
    std::string name = makePresetFilename(root_cnv, path);
    std::string full_path = makeFullPresetPath(root_cnv, name);

    bool rc = read(full_path.c_str());
    if (!rc)
        LIB_ERR << "can't read presets from " << full_path;
    else
        LIB_DBG << "presets readed from " << full_path;

    return rc;
}

bool PresetStorage::read(const char* path)
{
    t_binbuf* content = binbuf_new();
    int rc = binbuf_read(content, (char*)path, (char*)"", 0);

    std::vector<AtomList> lines;
    lines.push_back(AtomList());

    const int n = binbuf_getnatom(content);
    t_atom* lst = binbuf_getvec(content);
    for (int i = 0; i < n; i++) {
        lines.back().append(lst[i]);

        if (lst[i].a_type == A_SEMI) {
            lines.push_back(AtomList());
            continue;
        }
    }

    binbuf_free(content);

    // remove last empty list
    if (!lines.empty() && lines.back().empty())
        lines.pop_back();

    for (size_t i = 0; i < lines.size(); i++) {
        AtomList& line = lines[i];

        if (line.size() < 4)
            continue;

        if (line[0].isSymbol() && line[1].isFloat() && line[2].isSymbol()) {
            t_symbol* name = line[0].asSymbol();
            size_t index = line[1].asSizeT();
            t_symbol* sel = line[2].asSymbol();

            if (!hasPreset(name))
                continue;

            if (sel == &s_float) {
                setFloatValueAt(name, index, line[3].asFloat());
            } else if (sel == &s_symbol) {
                setSymbolValueAt(name, index, line[3].asSymbol());
            } else {
                AtomList lst = line.slice(3);
                if (lst.last() && lst.last()->isNone())
                    lst.remove(lst.size() - 1);

                if (sel == SYM_WITH_SPACES) {
                    std::string str = to_string(lst);

                    setSymbolValueAt(name, index, gensym(str.c_str()));
                } else if (sel == &s_list) {
                    setListValueAt(name, index, lst);
                } else {
                    setAnyValueAt(name, index, sel, lst);
                }
            }

        } else {
            LIB_ERR << "invalid preset line: " << line;
        }
    }

    return rc == 0;
}

AtomList PresetStorage::keys() const
{
    AtomList res;
    res.reserve(params_.size());

    PresetMap::const_iterator it;
    for (it = params_.begin(); it != params_.end(); ++it)
        res.append(it->first);

    return res;
}

bool PresetStorage::hasIndex(size_t sz) const
{
    if (sz >= MAX_PRESET_COUNT)
        return false;

    return !indexes_[sz].empty();
}

bool PresetStorage::hasPreset(t_symbol* name)
{
    return params_.find(name) != params_.end();
}

void PresetStorage::bindPreset(t_symbol* name)
{
    PresetMap::iterator it = params_.find(name);

    // create new preset
    if (it == params_.end()) {
        PresetPtr ptr = boost::make_shared<Preset>(name);
        std::pair<PresetMap::iterator, bool> res = params_.insert(PresetMap::value_type(name, ptr));
        if (!res.second) {
            LIB_ERR << "can't create preset: " << name;
            return;
        }

        it = res.first;
    }

    it->second->refCountUp();
}

void PresetStorage::unbindPreset(t_symbol* name)
{
    PresetMap::iterator it = params_.find(name);

    if (it == params_.end()) {
        LIB_ERR << "preset is not found: " << name;
        return;
    }

    it->second->refCountDown();
    int n = it->second->refCount();

    if (n == 0) {
        params_.erase(it);
    } else if (n < 0) {
        LIB_ERR << "preset ref count error: " << name;
    }
}

void PresetStorage::clearAll()
{
    params_.clear();
}

void PresetStorage::clearAll(size_t idx)
{
    if (!Preset::SYM_PRESET_ALL->s_thing)
        return;

    if (idx >= maxPresetCount()) {
        LIB_ERR << "[preset] "
                << "invalid preset index: " << idx
                << ". Should be less then: " << maxPresetCount();
        return;
    }

    t_atom a;
    SETFLOAT(&a, idx);
    pd_typedmess(Preset::SYM_PRESET_ALL->s_thing, Preset::SYM_CLEAR, 1, &a);
}

void PresetStorage::loadAll(size_t idx)
{
    if (!Preset::SYM_PRESET_ALL->s_thing)
        return;

    if (idx >= maxPresetCount()) {
        LIB_ERR << "[preset] "
                << "invalid preset index: " << idx
                << ". Should be less then: " << maxPresetCount();
        return;
    }

    t_atom a;
    SETFLOAT(&a, idx);
    pd_typedmess(Preset::SYM_PRESET_ALL->s_thing, Preset::SYM_LOAD, 1, &a);
}

void PresetStorage::storeAll(size_t idx)
{
    if (!Preset::SYM_PRESET_ALL->s_thing)
        return;

    if (idx >= maxPresetCount()) {
        LIB_ERR << "[preset] "
                << "invalid preset index: " << idx
                << ". Should be less then: " << maxPresetCount();
        return;
    }

    t_atom a;
    SETFLOAT(&a, idx);
    pd_typedmess(Preset::SYM_PRESET_ALL->s_thing, Preset::SYM_STORE, 1, &a);
}

void PresetStorage::updateAll()
{
    if (!Preset::SYM_PRESET_ALL->s_thing)
        return;

    pd_typedmess(Preset::SYM_PRESET_ALL->s_thing, Preset::SYM_UPDATE, 0, NULL);
}

PresetPtr PresetStorage::getOrCreate(t_symbol* name)
{
    PresetMap::iterator it = params_.find(name);
    if (it != params_.end())
        return it->second;

    PresetPtr new_param = boost::make_shared<Preset>(name);
    params_.insert(PresetMap::value_type(name, new_param));
    return new_param;
}

void PresetStorage::addPresetIndex(t_symbol* name, size_t idx)
{
    if (idx >= MAX_PRESET_COUNT)
        return;

    bool new_preset_index = indexes_[idx].empty();
    indexes_[idx].insert(name);

    if (new_preset_index && SYM_PRESET_UPDATE_INDEX_ADDR->s_thing) {
        t_atom a;
        SETFLOAT(&a, idx);
        pd_typedmess(SYM_PRESET_UPDATE_INDEX_ADDR->s_thing, SYM_PRESET_INDEX_ADD, 1, &a);
    }
}

void PresetStorage::removePresetIndex(t_symbol* name, size_t idx)
{
    if (idx >= MAX_PRESET_COUNT)
        return;

    indexes_[idx].erase(name);
    if (indexes_[idx].empty() && SYM_PRESET_UPDATE_INDEX_ADDR->s_thing) {
        t_atom a;
        SETFLOAT(&a, idx);
        pd_typedmess(SYM_PRESET_UPDATE_INDEX_ADDR->s_thing, SYM_PRESET_INDEX_REMOVE, 1, &a);
    }
}

Preset::Preset(t_symbol* name)
    : name_(name)
    , ref_count_(0)
{
    data_.assign(MAX_PRESET_COUNT, Message());
}

t_symbol* Preset::name() const
{
    return name_;
}

std::vector<Message>& Preset::data()
{
    return data_;
}

const std::vector<Message>& Preset::data() const
{
    return data_;
}

bool Preset::hasDataAt(size_t idx) const
{
    if (idx >= data_.size())
        return false;

    return !data_[idx].isNone();
}

bool Preset::hasDataTypeAt(size_t idx, Message::Type t) const
{
    if (idx >= data_.size())
        return false;

    return data_[idx].type() == t;
}

float Preset::floatAt(size_t idx, float def) const
{
    if (idx >= data_.size())
        return def;

    if (data_[idx].isFloat()) {
        t_float v = data_[idx].atomValue().asFloat();

        if (boost::math::isnan(v) || boost::math::isinf(v))
            return def;
        else
            return v;
    } else
        return def;
}

bool Preset::setFloatAt(size_t idx, float v)
{
    if (idx >= data_.size())
        return false;

    if (v == std::numeric_limits<float>::infinity())
        v = 0;

    data_[idx].setFloat(v);
    return true;
}

bool Preset::setSymbolAt(size_t idx, t_symbol* v)
{
    if (idx >= data_.size())
        return false;

    data_[idx].setSymbol(v);
    return true;
}

bool Preset::setListAt(size_t idx, const AtomList& l)
{
    if (idx >= data_.size())
        return false;

    data_[idx].setList(l);
    return true;
}

bool Preset::setAnyAt(size_t idx, t_symbol* sel, const AtomList& args)
{
    if (idx >= data_.size())
        return false;

    data_[idx].setAny(sel, args);
    return true;
}

t_symbol* Preset::symbolAt(size_t idx, t_symbol* def) const
{
    if (idx >= data_.size())
        return def;

    return data_[idx].isSymbol() ? data_[idx].atomValue().asSymbol() : def;
}

AtomList Preset::listAt(size_t idx, const AtomList& def) const
{
    if (idx >= data_.size())
        return def;

    return data_[idx].isList() ? data_[idx].listValue() : def;
}

AtomList Preset::anyAt(size_t idx, const AtomList& def) const
{
    if (idx >= data_.size())
        return def;

    return data_[idx].isAny() ? data_[idx].anyValue() : def;
}

bool Preset::clearAt(size_t idx)
{
    if (idx >= data_.size())
        return false;

    data_[idx] = Message();
    return true;
}
}
