#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <vector>
#include <sstream>

// Base component
class Component {
public:
    virtual ~Component() = default;
    virtual void Update() = 0;
    virtual std::string Serialize() const = 0;   // 🔹 new
};

// --- Interfaces ---
class Drawable {
public:
    virtual void Draw() = 0;
    virtual ~Drawable() = default;
};

class PhysicsBody {
public:
    virtual void ApplyForce(float fx, float fy) = 0;
    virtual ~PhysicsBody() = default;
};

// --- Components ---
class RenderComponent : public Component, public Drawable {
    int layer = 0;
public:
    RenderComponent(int l = 0) : layer(l) {}
    void Update() override {
        std::cout << "Updating Render Component (layer=" << layer << ")\n";
    }
    void Draw() override {
        std::cout << "Drawing something on layer " << layer << "\n";
    }
    std::string Serialize() const override {
        std::ostringstream oss;
        oss << "RenderComponent { layer=" << layer << " }";
        return oss.str();
    }
};

class PhysicsComponent : public Component, public PhysicsBody {
    float mass = 1.0f;
public:
    PhysicsComponent(float m = 1.0f) : mass(m) {}
    void Update() override {
        std::cout << "Updating Physics Component (mass=" << mass << ")\n";
    }
    void ApplyForce(float fx, float fy) override {
        std::cout << "Applying force (" << fx << ", " << fy << ") to mass " << mass << "\n";
    }
    std::string Serialize() const override {
        std::ostringstream oss;
        oss << "PhysicsComponent { mass=" << mass << " }";
        return oss.str();
    }
};

// --- Manager ---
class ComponentManager {
private:
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<Component>>> components;

public:
    void AddComponent(std::unique_ptr<Component> comp) {
        components[typeid(*comp)].push_back(std::move(comp));
    }

    template <typename T>
    std::vector<T*> GetComponents() {
        std::vector<T*> result;
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            for (auto& c : it->second) {
                if (auto ptr = dynamic_cast<T*>(c.get())) {
                    result.push_back(ptr);
                }
            }
        }
        return result;
    }

    template <typename Interface>
    std::vector<Interface*> GetByInterface() {
        std::vector<Interface*> result;
        for (auto& [type, compList] : components) {
            for (auto& comp : compList) {
                if (auto ptr = dynamic_cast<Interface*>(comp.get())) {
                    result.push_back(ptr);
                }
            }
        }
        return result;
    }

    void UpdateAll() {
        for (auto& [type, compList] : components) {
            for (auto& comp : compList) {
                comp->Update();
            }
        }
    }

    // New: serialize all components to a single string
    std::string SerializeAll() const {
        std::ostringstream oss;
        for (auto& [type, compList] : components) {
            for (auto& comp : compList) {
                oss << comp->Serialize() << "\n";
            }
        }
        return oss.str();
    }
};

// ----------------- Test -------------------
int main() {
    ComponentManager manager;

    manager.AddComponent(std::make_unique<RenderComponent>(1));
    manager.AddComponent(std::make_unique<RenderComponent>(2));
    manager.AddComponent(std::make_unique<PhysicsComponent>(10.0f));

    manager.UpdateAll();

    std::cout << "\n--- Serialized Output ---\n";
    std::cout << manager.SerializeAll();

    return 0;
}
