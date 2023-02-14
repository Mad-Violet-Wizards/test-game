#pragma once

class C_Direction;

class C_ProjectileGenerator : public Component
{

  public:

    C_ProjectileGenerator(Object *owner, ObjectCollection *objectCollection);

    void Awake() override;

    void GenerateProjectile(const std::string &name);

  private:

    ObjectCollection *m_objectCollection;

    std::shared_ptr<C_Direction> m_direction;

};