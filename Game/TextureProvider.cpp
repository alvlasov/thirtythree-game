#include "TextureProvider.h"

namespace thirtythree {

void TextureProvider::LoadPlayerTexturesFromDirectory(std::string directory) {
    LOG_INFO("Loading textures");
    auto file_names = GetFileNamesInDirectory(directory);
    for (auto& name : file_names) {
        player_textures_.push_back(sf::Texture());
        LOG_INFO(name);
        if (!player_textures_.back().loadFromFile(name)) {
            LOG_ERROR("Failed to load texture: " << name);
        } else {
            player_textures_.back().setSmooth(true);
        }
    }
}


sf::Texture* TextureProvider::GetRandomPlayerTexture() {
    int index = rand_->UniformInt(player_textures_.size() - 1);
    return &player_textures_[index];
}

std::vector<std::string> TextureProvider::GetFileNamesInDirectory(std::string directory)
{
    std::vector<std::string> out;
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return out; /* No files found */

    do {
        const std::string file_name = file_data.cFileName;
        const std::string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
    return out;
}


}
