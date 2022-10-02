#pragma once

#include "arcore_c_api.h"

namespace arcoreapp {

/**
 * Handle the creation and update of a GPU texture.
 **/
class Texture {
 public:
  Texture() = default;
  ~Texture() = default;

  void CreateOnGlThread();
  void UpdateWithDepthImageOnGlThread(const ArSession& session,
                                      const ArFrame& frame);
  unsigned int GetTextureId() { return texture_id_; }

  unsigned int GetWidth() { return width_; }

  unsigned int GetHeight() { return height_; }

 private:
  unsigned int texture_id_ = 0;
  unsigned int width_ = 1;
  unsigned int height_ = 1;
};
}  // namespace arcoreapp

