/**
 * @file login.h
 * @brief Login dialog header file.
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

/**
 * @class login
 * @brief A simple login dialog widget.
 *
 * This class provides a basic login dialog with input fields, buttons,
 * and error handling. It can be used as is or extended to suit specific
 * needs.
 */

class login : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new login dialog instance.
     *
     * @param parent The parent widget for this dialog (optional).
     */
    explicit login(QWidget *parent = nullptr);

    /**
     * @brief Destroys the login dialog instance.
     */
    ~login();

private slots:
    /**
     * @brief Handles link activation in the login dialog.
     *
     * This slot is triggered when a link in the dialog is activated (e.g.,
     * clicked).
     *
     * @param link The URL of the link that was activated.
     */
    void on_label_5_linkActivated(const QString &link);

    /**
     * @brief Handles button box acceptance or rejection.
     */
    void on_pushButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::login *ui; ///< The UI component for this dialog.
};

#endif // LOGIN_H
