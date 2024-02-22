#pragma once

#ifdef POTATOS_ENGINE_EXPORTS
#define POTATOS_ENGINE_API __declspec(dllexport)
#else
#define POTATOS_ENGINE_API __declspec(dllimport)
#endif