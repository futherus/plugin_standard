#pragma once

template <typename T>
struct Pair
{
    T x;
    T y;
};

class IWidget
{
private:

public:
    virtual ~IWidget() = default;

    /**
     * Set position of widget.
     * 
     * \param point new absolute widget position in pixels.
     */
    virtual void set_pos(Pair<int> point) = 0;
    /**
     * Get position of widget.
     * 
     * \return absolute widget position in pixels.
     */
    virtual Pair<int> get_pos() = 0;

    /**
     * Get size of widget bounding box.
     * 
     * \return size of bounding box in pixels.
     */
    virtual Pair<int> get_size() = 0;

    /**
     * Checks if point is in widget area.
     * 
     * \param point absolute point position in pixels.
     */
    virtual void contains(Pair<int> point) = 0;

    /**
     * Trigger mouse events of widgets.
     * 
     * \param point absolute mouse position.
     */
    virtual void on_mouse_press(Pair<int> point) = 0;
    virtual void on_mouse_release(Pair<int> point) = 0;
    virtual void on_mouse_move(Pair<int> point) = 0;

    /**
     * Trigger keyboard events of widgets.
     * 
     * \param key key code.
     */
    virtual void on_key_press(int key) = 0;
    virtual void on_key_release(int key) = 0;

    /**
     * Draw widget on screen.
     * 
     * \param screen array of screen pixels.
     * \param width screen width in pixels.
     * \param height screen height in pixels.
     */
    virtual void draw(unsigned int* screen, int width, int height) = 0;
};

class IPushButton : public IWidget
{
private:
    /**
     * Function to trigger on event.
     * 
     * \param self pointer to object itself (this).
     */
    void (*signal_)(IPushButton* self);

    /**
     * State of button.
     * 
     * true (1) - pressed.
     * false (0) - released.
     */
    bool state_;

public:
    virtual ~IPushButton() = default;

    /**
     * Set signal function.
     * 
     * \param signal pointer to signal function.
     */
    virtual void set_signal(void (*signal)(IPushButton*)) = 0;

    /**
     * Set button state.
     * 
     * This function DOES NOT trigger signal.
     * 
     * \param state new state value.
     */
    void set_state(bool state) { state_ = state; }

    /**
     * Acquire button state.
     * 
     * \return state value.
     */
    bool get_state() { return state_; }
};

class ITool
{
private:

public:
    virtual ~ITool() = default;

    /**
     * Apply tool to pixmap.
     * 
     * Performs tool action on pixmap, drawing over existing pixels.
     * 
     * \param pixmap array of pixels to draw on.
     * \param width width of pixmap.
     * \param height height of pixmap.
     * \param point relative position of tool application in pixels.
     */
    virtual void apply(unsigned int* pixmap, int width, int height, Pair<int> point) = 0;

    /**
     * Deactivate tool.
     */
    virtual void deactivate() = 0;
};

class IPlugin
{
private:
    /**
     * Pointer to plugin tool.
     */
    ITool* tool_;

    /**
     * Property pallette.
     * 
     * Meaned to connect to property pallette manager.
     */
    IWidget* props_;

    /**
     * Tool activate/deactivate button.
     * 
     * Meaned to connect to tool pallette.
     */
    IPushButton* tool_button_;

public:
    IPlugin() = default;
    IPlugin(IPlugin&) = delete;
    IPlugin& operator=(IPlugin&) = delete;
    virtual ~IPlugin() = default;

    ITool* get_tool() { return tool_; }
    IWidget* get_props() { return props_; }
    IPushButton* get_tool_button() { return tool_button_; }

    void set_tool(ITool* tool) { tool_ = tool; }
    void set_props(IWidget* props) { props_ = props; }
    void set_tool_button(IPushButton* tool_button) { tool_button_ = tool_button; }
};

/**
 * Get plugin objects.
 * 
 * Initializes plugin and provides plugin api.
 */
extern "C" IPlugin* get_plugin();

/**
 * Deinitializes plugin.
 */
extern "C" void destroy_plugin();
