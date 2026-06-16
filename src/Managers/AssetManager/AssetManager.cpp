#include "AssetManager.hpp"

#include <iostream>

namespace AssetManager {
    void Init() {
        std::cout << "Initializing AssetManager...\n";
        FindAssetPaths();
    }

    void FindAssetPaths() {}

} // namespace AssetManager
