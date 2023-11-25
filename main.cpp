/// @brief Centsible
/// @details A program that allows users to track their spending/investing habits.
/// @brief Created by Ethan Edwards on 11/19/2023.

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize( 200, 100 );
    button.show();
    return QApplication::exec();
}
