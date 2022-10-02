#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <cstdlib>

#include "arcore_c_api.h"
#include "util.h"

namespace arcoreapp {

// This class renders the passthrough camera image into the OpenGL frame.
class BackgroundRenderer {
 public:
  BackgroundRenderer() = default;
  ~BackgroundRenderer() = default;

  // Sets up OpenGL state.  Must be called on the OpenGL thread and before any
  // other methods below.
  void InitializeGlContent(AAssetManager* asset_manager, int depthTextureId);

  // Draws the background image.  This methods must be called for every ArFrame
  // returned by ArSession_update() to catch display geometry change events.
  //  debugShowDepthMap Toggles whether to show the live camera feed or latest
  //  depth image.
  void Draw(const ArSession* session, const ArFrame* frame,
            bool debug_show_depth_map);

  // Returns the generated texture name for the GL_TEXTURE_EXTERNAL_OES target.
  GLuint GetTextureId() const;

 private:
  static constexpr int kNumVertices = 4;

  GLuint camera_program_;
  GLuint depth_program_;

  GLuint camera_texture_id_;
  GLuint depth_texture_id_;
  GLuint depth_color_palette_id_;

  GLuint camera_position_attrib_;
  GLuint camera_tex_coord_attrib_;
  GLuint camera_texture_uniform_;

  GLuint depth_texture_uniform_;
  GLuint depth_color_palette_uniform_;
  GLuint depth_position_attrib_;
  GLuint depth_tex_coord_attrib_;

  float transformed_uvs_[kNumVertices * 2];
  bool uvs_initialized_ = false;
};
}  // namespace arcoreapp
