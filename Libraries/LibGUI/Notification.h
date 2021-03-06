#pragma once

#include <LibCore/Object.h>
#include <LibGfx/Bitmap.h>

namespace GUI {

class Notification : public Core::Object {
    C_OBJECT(Notification);

public:
    virtual ~Notification() override;

    const String& text() const { return m_text; }
    void set_text(const String& text) { m_text = text; }

    const String& title() const { return m_title; }
    void set_title(const String& title) { m_title = title; }

    const Gfx::Bitmap* icon() const { return m_icon; }
    void set_icon(const Gfx::Bitmap* icon) { m_icon = icon; }

    void show();

private:
    Notification();

    String m_title;
    String m_text;
    RefPtr<Gfx::Bitmap> m_icon;
};

}
