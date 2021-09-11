#include "Scene/Scene.hpp"

class SceneMenu : public Scene
{
  public:

	SceneMenu();
	~SceneMenu();

	void OnCreate() override;
	void OnDestroy() override;

	void Update(float deltaTime) override;
	void Draw(Window& window) override;
};