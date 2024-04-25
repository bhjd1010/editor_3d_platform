
#include "ui_viewer.h"

#include <easy3d/core/point_cloud.h>
#include <easy3d/renderer/text_renderer.h>
#include <easy3d/renderer/camera.h>

#include <3rd_party/imgui/misc/fonts/imgui_fonts_droid_sans.h>
#include <3rd_party/imgui/imgui.h>
#include <3rd_party/imgui/backends/imgui_impl_glfw.h>
#include <3rd_party/imgui/backends/imgui_impl_opengl3.h>
#include <3rd_party/glfw/include/GLFW/glfw3.h>
#include "easy3d/renderer/drawable_points.h"
#include "element/element.h"

using namespace easy3d;

namespace gmv {

    ImGuiContext *UIViewer::context_ = nullptr;

    UIViewer::UIViewer(
            const std::string &title /* = "Easy3D ImGui Viewer" */,
            int samples /* = 4 */,
            int gl_major /* = 3 */,
            int gl_minor /* = 2 */,
            bool full_screen /* = false */,
            bool resizable /* = true */,
            int depth_bits /* = 24 */,
            int stencil_bits /* = 8 */,
            int width /* = 960 */,
            int height /* = 800 */
    ) : Viewer(title, samples, gl_major, gl_minor, full_screen, resizable, depth_bits, stencil_bits, width, height) {
#if defined(_WIN32) && defined(_MSC_VER)
        glfwInit();
#endif
    }


    UIViewer::~UIViewer() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext(context_);
    }


    void UIViewer::init() {
        Viewer::init();

        if (!context_) {
            // Setup ImGui binding
            IMGUI_CHECKVERSION();

            context_ = ImGui::CreateContext();

            const char *glsl_version = "#version 150";
            ImGui_ImplGlfw_InitForOpenGL(window_, true);
            ImGui_ImplOpenGL3_Init(glsl_version);
            ImGuiIO &io = ImGui::GetIO();
            io.WantCaptureKeyboard = true;
            io.WantTextInput = true;
            io.IniFilename = nullptr;
            ImGui::StyleColorsLight();
            ImGuiStyle &style = ImGui::GetStyle();
            style.FrameRounding = 5.0f;

            // load font
            reload_font();
        }
    }


    float UIViewer::pixel_ratio() {
        // Computes pixel ratio for hidpi devices
        int fw = framebuffer_width();
        int vw = width();
        return static_cast<float>(fw) / static_cast<float>(vw);
    }


    void UIViewer::reload_font(int font_size) {
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->Clear();
        io.Fonts->AddFontFromMemoryCompressedTTF(droid_sans_compressed_data, droid_sans_compressed_size,
                                                 static_cast<float>(font_size) * dpi_scaling());
        io.FontGlobalScale = 1.0f / pixel_ratio();
        ImGui_ImplOpenGL3_DestroyDeviceObjects();
    }


    void UIViewer::post_resize(int w, int h) {
        Viewer::post_resize(w, h);
        if (context_) {
            ImGui::GetIO().DisplaySize.x = float(w);
            ImGui::GetIO().DisplaySize.y = float(h);
        }
    }


    bool UIViewer::callback_event_cursor_pos(double x, double y) {
        if (ImGui::GetIO().WantCaptureMouse)
            return true;
        else
            return Viewer::callback_event_cursor_pos(x, y);
    }


    bool UIViewer::callback_event_mouse_button(int button, int action, int modifiers) {
        if (ImGui::GetIO().WantCaptureMouse)
            return true;
        else
            return Viewer::callback_event_mouse_button(button, action, modifiers);
    }


    bool UIViewer::callback_event_keyboard(int key, int action, int modifiers) {
        if (ImGui::GetIO().WantCaptureKeyboard)
            return true;
        else
            return Viewer::callback_event_keyboard(key, action, modifiers);
    }


    bool UIViewer::callback_event_character(unsigned int codepoint) {
        if (ImGui::GetIO().WantCaptureKeyboard)
            return true;
        else
            return Viewer::callback_event_character(codepoint);
    }


    bool UIViewer::callback_event_scroll(double dx, double dy) {
        if (ImGui::GetIO().WantCaptureMouse)
            return true;
        else
            return Viewer::callback_event_scroll(dx, dy);
    }


    void UIViewer::pre_draw() {
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        Viewer::pre_draw();
    }


    void UIViewer::post_draw() {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 8));
        if (ImGui::BeginMainMenuBar()) {
            draw_menu_file();
            draw_menu_view();

            menu_height_ = ImGui::GetWindowHeight();
            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleVar();

        for (auto &painter: uiPainters) {
            std::invoke(painter);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        texter_ = nullptr;
        Viewer::post_draw();
    }

    void UIViewer::draw_menu_file() {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O"))
                open();
            if (ImGui::MenuItem("Save As...", "Ctrl+S"))
                save();

            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Alt+F4"))
                glfwSetWindowShouldClose(window_, GLFW_TRUE);

            ImGui::EndMenu();
        }
    }

    void UIViewer::draw_menu_view() {
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Snapshot", nullptr))
                snapshot();

            ImGui::EndMenu();
        }
    }

    bool UIViewer::DeleteDrawableById(ElementId id) {
        auto ite = std::find_if(drawables_.begin(), drawables_.end(),
                                [&](Drawable *p) { return p->name() == id.ToString(); });
        if (ite != drawables_.end()) {
            delete_drawable(*ite);
            return true;
        }
        throw ("未找到Drawable");
        return false;
    }

    easy3d::Drawable *UIViewer::GetDrawableById(ElementId id) {
        auto ite = std::find_if(drawables_.begin(), drawables_.end(),
                                [&](Drawable *p) { return p->name() == id.ToString(); });
        if (ite != drawables_.end()) {
            return *ite;
        }
        return nullptr;
    }

    bool UIViewer::DrawGeomObject(const Element *pEle) {
        std::vector<easy3d::Drawable *> drawables = pEle->GetRenderNode();
        if (drawables.size()) {
            for (auto drawable: drawables) {
                this->add_drawable(drawable);
            }

            return true;
        }
        return false;
    }

    bool UIViewer::DeleteDrawableByName(const std::string &name) {
        auto ite = std::find_if(drawables_.begin(), drawables_.end(), [&](Drawable *p) { return p->name() == name; });
        if (ite != drawables_.end()) {
            delete_drawable(*ite);
            return true;
        }
        return false;
    }

    void UIViewer::registerUiPainer(const std::function<void()> &painter) {
        uiPainters.push_back(painter);
    }

    bool UIViewer::mouse_press_event(int x, int y, int button, int modifiers) {
        std::shared_ptr<MouseEventArgs> pArgs = NEW_AS_SHARED_PTR(MouseEventArgs, x, y, button, modifiers);
        EventManager::Get()->SendEvent(EventType::MouseEvent, pArgs.get());

        return Viewer::mouse_press_event(x, y, button, modifiers);
    }
}
