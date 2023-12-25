
class RenderContext {
public:
    RenderContext() { }
};

class Renderable {
public:
    virtual void render(const RenderContext&) const = 0;
};

class InputHandler {
public:
    virtual void handle_inputs() = 0;
};

#define TO_BE_IMPLEMENTED() assert(0)
