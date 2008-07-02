#include "configdialog.h"
#include <QSettings>

ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent),
      m_first(true)
{
}

void ConfigDialog::on_draw_potential_stateChanged(int state)
{
}

int ConfigDialog::exec()
{
    return QDialog::exec();
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::draw(int state)
{
    /// @todo implement me
}
