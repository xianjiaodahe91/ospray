// ======================================================================== //
// Copyright 2009-2018 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#ifdef _WIN32
#  ifdef ospray_sg_EXPORTS
#    define OSPSG_INTERFACE __declspec(dllexport)
#  else
#    define OSPSG_INTERFACE __declspec(dllimport)
#  endif
#else
#  define OSPSG_INTERFACE
#endif

// sg components
#include "common/Data.h"
#include "common/FrameBuffer.h"
#include "common/Renderable.h"
#include "common/Transform.h"

#include "camera/Camera.h"

#include "geometry/Geometry.h"

#include "importer/Importer.h"

#include "volume/Volume.h"

#include "Renderer.h"

namespace ospray {
  namespace sg {

    /* This "ties" 3 major components together: framebuffer, renderer, and
       camera
     */
    struct OSPSG_INTERFACE Frame : public Node
    {
      Frame();
      ~Frame() override = default;

      // Node interface //

      std::string toString() const override;

      void preCommit(RenderContext &ctx) override;
      void postCommit(RenderContext &ctx) override;

      // Frame interface //

      void renderFrame(bool verifyCommit = true);

      OSPPickResult pick(const vec2f &pickPos);
      float getLastVariance() const;

    private:

      // Data members //

      OSPCamera currentCamera {nullptr};
      OSPRenderer currentRenderer {nullptr};
      OSPFrameBuffer currentFB {nullptr};

      bool clearFB {true};

      int numAccumulatedFrames{0};
      int frameAccumulationLimit{-1};
    };

  } // ::ospray::sg
} // ::ospray

