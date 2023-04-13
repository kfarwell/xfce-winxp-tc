#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <wintc-comgtk.h>

#include "application.h"
#include "dialog.h"

//
// GTK OOP CLASS/INSTANCE DEFINITIONS
//
struct _WinTCNewPwrDlgDialogPrivate
{
    int blah;
};

struct _WinTCNewPwrDlgDialogClass
{
    GtkApplicationWindowClass __parent__;
};

struct _WinTCNewPwrDlgDialog
{
    GtkApplicationWindow __parent__;

    WinTCNewPwrDlgDialogPrivate* priv;
};

//
// FORWARD DECLARATIONS
//
static void wintc_npwrdlg_dialog_finalize(
    GObject* object
);

//
// GTK TYPE DEFINITION & CTORS
//
G_DEFINE_TYPE_WITH_CODE(
    WinTCNewPwrDlgDialog,
    wintc_npwrdlg_dialog,
    GTK_TYPE_APPLICATION_WINDOW,
    G_ADD_PRIVATE(WinTCNewPwrDlgDialog)
)

static void wintc_npwrdlg_dialog_class_init(
    WinTCNewPwrDlgDialogClass* klass
)
{
    GObjectClass* object_class = G_OBJECT_CLASS(klass);

    object_class->finalize = wintc_npwrdlg_dialog_finalize;
}

static void wintc_npwrdlg_dialog_init(
    WinTCNewPwrDlgDialog* self
)
{
    gtk_window_set_decorated(GTK_WINDOW(self), FALSE);
    gtk_window_set_title(GTK_WINDOW(self), _("Shutdown Windows"));

    wintc_widget_add_style_class(GTK_WIDGET(self), "npwrdlg");

    // Populate window
    //
    GtkBuilder* builder  = gtk_builder_new_from_resource(
                               "/uk/oddmatics/wintc/npwrdlg/pwropts.ui"
                           );
    GtkWidget*  main_box = GTK_WIDGET(
                               gtk_builder_get_object(builder, "main-box")
                           );

    gtk_container_add(GTK_CONTAINER(self), main_box);
}

//
// FINALIZE
//
static void wintc_npwrdlg_dialog_finalize(
    GObject* object
)
{
    (*G_OBJECT_CLASS(wintc_npwrdlg_dialog_parent_class)->finalize) (object);
}

//
// PUBLIC FUNCTIONS
//
GtkWidget* wintc_npwrdlg_dialog_new(
    WinTCNewPwrDlgApplication* app
)
{
    return GTK_WIDGET(
        g_object_new(
            TYPE_WINTC_NPWRDLG_DIALOG,
            "application", GTK_APPLICATION(app),
            NULL
        )
    );
}
