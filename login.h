#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

/**
 * @class login
 * @brief Represents the login dialog for the application.
 *
 * This class provides the login interface, allowing users to enter their
 * credentials and authenticate into the system.
 */
class login : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the login dialog.
     * @param parent Optional parent widget.
     */
    explicit login(QWidget *parent = nullptr);

    /// @brief Destructor for the login dialog.
    ~login();

private slots:
    /// @brief Handles the event when the login button is clicked.
    void on_pushButton_clicked();

    /// @brief Handles the event when the accept button in the button box is clicked.
    void on_buttonBox_accepted();

    /// @brief Handles the event when the reject button in the button box is clicked.
    void on_buttonBox_rejected();

private:
    Ui::login *ui;  /**< Pointer to the UI instance of the login dialog. */
};

#endif // LOGIN_H
