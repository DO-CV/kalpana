#pragma once

#include <memory>
#include <vector>

#include <DO/Kalpana/3D.hpp>


namespace DO { namespace Kalpana {

  class Scene
  {
  public:
    Scene() = default;

    std::vector<std::unique_ptr<Object3D>> _objects;
  };

} /* namespace Kalpana */
} /* namespace DO */
