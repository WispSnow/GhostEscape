#include "asset_store.h"

void AssetStore::clean()
{
    for (auto &texture : textures_)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures_.clear();

    for (auto &sound : sounds_)
    {
        MIX_DestroyAudio(sound.second);
    }
    sounds_.clear();

    for (auto &music : music_)
    {
        MIX_DestroyAudio(music.second);
    }
    music_.clear();

    for (auto &font : fonts_)
    {
        TTF_CloseFont(font.second);
    }
    fonts_.clear();
}

void AssetStore::loadImage(const std::string &file_path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer_, file_path.c_str());
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", file_path.c_str());
        return;
    }
    // textures_[file_path] = texture;         // 可行，会覆盖之前的值。
    textures_.emplace(file_path, texture);   // 如果已经存在，则不会插入。
}

void AssetStore::loadSound(const std::string &file_path)
{
    MIX_Audio *sound = MIX_LoadAudio(NULL, file_path.c_str(), true);
    if (sound == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s", file_path.c_str());
        return;
    }
    sounds_.emplace(file_path, sound);
}

void AssetStore::loadMusic(const std::string &file_path)
{
    MIX_Audio *music = MIX_LoadAudio(NULL, file_path.c_str(), false);
    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", file_path.c_str());
        return;
    }
    music_.emplace(file_path, music);
}

void AssetStore::loadFont(const std::string &file_path, int font_size)
{
    TTF_Font *font = TTF_OpenFont(file_path.c_str(), font_size);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", file_path.c_str());
        return;
    }
    fonts_.emplace(file_path + std::to_string(font_size), font);
}

SDL_Texture *AssetStore::getImage(const std::string &file_path)
{
    auto iter = textures_.find(file_path);
    if (iter == textures_.end())        // 如果没有找到，则载入。
    {
        loadImage(file_path);
        iter = textures_.find(file_path);
    }
    if (iter == textures_.end())        // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get image: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

MIX_Audio *AssetStore::getSound(const std::string &file_path)
{
    auto iter = sounds_.find(file_path);
    if (iter == sounds_.end())          // 如果没有找到，则载入。
    {
        loadSound(file_path);
        iter = sounds_.find(file_path);
    }
    if (iter == sounds_.end())          // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get sound: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

MIX_Audio *AssetStore::getMusic(const std::string &file_path)
{
    auto iter = music_.find(file_path);
    if (iter == music_.end())           // 如果没有找到，则载入。
    {
        loadMusic(file_path);
        iter = music_.find(file_path);
    }
    if (iter == music_.end())           // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get music: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

TTF_Font *AssetStore::getFont(const std::string &file_path, int font_size)
{
    auto iter = fonts_.find(file_path + std::to_string(font_size));
    if (iter == fonts_.end())           // 如果没有找到，则载入。
    {
        loadFont(file_path, font_size);
        iter = fonts_.find(file_path + std::to_string(font_size));
    }
    if (iter == fonts_.end())           // 如果载入失败，则返回空指针。
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font: %s", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}