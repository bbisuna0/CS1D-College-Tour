#include "login.h"
#include "ui_login.h"
#include "reguser.h"
#include "main.h"
#include "utility.h"

extern User myUser;
int login_count = 0;

/**
 * @brief Constructs a new login dialog instance.
 *
 * This constructor initializes the login dialog's UI component and sets up
 * its event handling.
 *
 * @param parent The parent widget for this dialog (optional).
 */
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    /**
     * Set up the UI component and initialize the dialog's layout.
     */
    ui->setupUi(this);
}

/**
 * @brief Destroys the login dialog instance.
 *
 * This destructor cleans up any resources used by the login dialog, such as
 * deleting the UI component.
 */
login::~login()
{
    delete ui;
}

/**
 * @slot Handles link activation in the login dialog.
 *
 * When a link in the dialog is activated (e.g., clicked), this slot is triggered.
 * In this case, it shows a registration user dialog.
 *
 * @param link The URL of the link that was activated.
 */
void login::on_label_5_linkActivated(const QString &link)
{
    reguser r;
    /**
     * Show the registration user dialog.
     */
    r.show();
}

/**
 * @slot Handles button box rejection in the login dialog.
 *
 * When the user rejects the login dialog, this slot is triggered. In this case,
 * it sets the myUser object's uname and login_ok members to "error" and false,
 * respectively, and closes the dialog.
 */
void login::on_buttonBox_rejected()
{
    /**
     * Set the myUser object'suname and login_ok members.
     */
    myUser.uname = "error";
    myUser.login_ok = false;
    myUser.admin = false;
    /**
     * Close the dialog.
     */
    this->close();
}

/**
 * @slot Handles button box acceptance in the login dialog.
 *
 * When the user accepts the login dialog, this slot is triggered. In this case,
 * it checks the entered username and password against the stored credentials
 * and updates the myUser object accordingly.
 */
void login::on_buttonBox_accepted()
{
    /**
     * Get the username and password from the UI component.
     */
    QString uname = ui->le_username->text();
    QString pass = ui->le_password->text();

    bool login_ok = checkPassword(uname, pass, myUser.admin, myUser.uid);

    // Update the login count
    login_count++;

    if (login_ok)
    {
        /**
         * Set the myUser object's uname and login_ok members.
         */
        myUser.uname = uname;
        myUser.login_ok = true;

        /**
         * Close the dialog.
         */
        this->close();
    }
    else
    {
        // Update the myUser object's login_ok member
        myUser.login_ok = false;
        myUser.admin = false;

        if (login_count > 2)
        {
            /**
             * Show a warning message and close the dialog.
             */
            QMessageBox::warning(0, QObject::tr("Too many invalid login attempt"),
                                 "Too many invalid login attempts.");

            this->close();
        }
    }
}

/**
 * @slot Handles button click in the login dialog.
 *
 * When the user clicks the button in the dialog, this slot is triggered. In this
 * case, it shows a registration user dialog with modal behavior and closes
 * the original dialog.
 */
void login::on_buttonBox_clicked()
{
    reguser r;
    /**
     * Show the registration user dialog with modal behavior.
     */
    r.setModal(true);
    r.setWindowFlags(r.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    /**
     * Execute the registration user dialog.
     */
    r.exec();
}
