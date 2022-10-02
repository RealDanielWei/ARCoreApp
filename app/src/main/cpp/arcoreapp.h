#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <jni.h>

#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include "arcore_c_api.h"
#include "background_renderer.h"
#include "glm.h"
#include "texture.h"
#include "util.h"

namespace arcoreapp {

// ARCoreApp handles all application logics.
class ARCoreApp {
 public:
  // Constructor and deconstructor.
  explicit ARCoreApp(AAssetManager* asset_manager);
  ~ARCoreApp();

  // OnPause is called on the UI thread from the Activity's onPause method.
  void OnPause();

  // OnResume is called on the UI thread from the Activity's onResume method.
  void OnResume(JNIEnv* env, void* context, void* activity);

  // OnSurfaceCreated is called on the OpenGL thread when GLSurfaceView
  // is created.
  void OnSurfaceCreated();

  // OnDisplayGeometryChanged is called on the OpenGL thread when the
  // render surface size or display rotation changes.
  //
  // @param display_rotation: current display rotation.
  // @param width: width of the changed surface view.
  // @param height: height of the changed surface view.
  void OnDisplayGeometryChanged(int display_rotation, int width, int height);

  // OnDrawFrame is called on the OpenGL thread to render the next frame.
  void OnDrawFrame(bool depthColorVisualizationEnabled,
                   bool useDepthForOcclusion);

  // OnTouched is called on the OpenGL thread after the user touches the screen.
  // @param x: x position on the screen (pixels).
  // @param y: y position on the screen (pixels).
  void OnTouched(float x, float y);

  // Returns true if depth is supported.
  bool IsDepthSupported();

  void OnSettingsChange();

 private:
  glm::mat3 GetTextureTransformMatrix(const ArSession* session,
                                      const ArFrame* frame);
  ArSession* ar_session_ = nullptr;
  ArFrame* ar_frame_ = nullptr;

  bool install_requested_ = false;
  int width_ = 1;
  int height_ = 1;
  int display_rotation_ = 0;

  AAssetManager* const asset_manager_;

  BackgroundRenderer background_renderer_;
  Texture depth_texture_;

  void ConfigureSession();

};
}  // namespace arcoreapp
