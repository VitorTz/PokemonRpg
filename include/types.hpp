#pragma once
#include <cstdint>
#include <map>
#include <vector>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;
    typedef std::vector<std::pair<float, pk::entity_t>> ZindexEntityVector;
    typedef std::map<pk::zindex_t, pk::ZindexEntityVector> Camera;
    
} // namespace pk
