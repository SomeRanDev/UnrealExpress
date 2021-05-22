#pragma once

#define uinit(name) name = nullptr; for(auto& it = *CreateDefaultSubobject<std::remove_pointer_t<decltype(name)>>(TEXT(#name)); name == nullptr; name = &it)
