
// signpost pointing to the real files
#pragma once

#include "../../mini-yaml/yaml/Yaml.hpp"

#ifdef MINI_YAML_CPP
#   include "../../mini-yaml/yaml/Yaml.cpp"
#endif


// =============================================================================
// add extra functions for YAML

namespace Yaml
{
	//! returns an empty object - i couldn't work this out
	inline
	Yaml::Node Object()noexcept
	{
		static Yaml::Node object;
		if (object.IsNone())
			Yaml::Parse(object, std::string("{}"));
		return object;
	}

	inline
	std::string Serialize(const Yaml::Node& node) noexcept
	{
		std::string text;
		Yaml::Serialize(node, text);
		return text;
	}

	template<class V>
	struct pairs
	{
		Yaml::Node& _yaml;

		struct it
		{
			Yaml::Iterator _it;
			bool _empty;

			bool operator==(const it& _) noexcept
			{
				assert(_empty == _._empty);
				return _empty || _it == _._it;
			}

			bool operator!=(const it& _) noexcept
			{
				return !(*this == _);
			}

			it& operator ++() noexcept { _it++; return *this; }

			std::pair<std::string, V> operator*() noexcept;
		};

		it begin() noexcept
		{
			return (it{ _yaml.Size() == 0 ? _yaml.End() : _yaml.Begin(), 0 == _yaml.Size() });
		}

		it end() noexcept { return (it{ _yaml.End(), 0 == _yaml.Size() }); }
	};


}

template<>
inline std::pair<std::string, std::string> Yaml::pairs<std::string>::it::operator*() noexcept
{
	return std::pair(
		(*_it).first,
		(*_it).second.As<std::string>()
	);
}

template<>
inline std::pair<std::string, Yaml::Node> Yaml::pairs<Yaml::Node>::it::operator*() noexcept
{
	return std::pair((*_it).first, (*_it).second);
}
