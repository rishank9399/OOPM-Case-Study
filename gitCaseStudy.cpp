#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum class EmailStatus {
    UNREAD,
    READ
};

class Email {

    private:
    string sender;
    string subject;
    string body;
    EmailStatus status;

public:
    Email(const string& sender, const string& subject, const string& body)
        : sender(sender), subject(subject), body(body), status(EmailStatus::UNREAD) {}

    void markAsRead() {
        status = EmailStatus::READ;
    }

    bool isRead() const {
        return status == EmailStatus::READ;
    }

    const string& getSender() const {
        return sender;
    }

    const string& getSubject() const {
        return subject;
    }

    const string& getBody() const {
        return body;
    }
};

class Inbox {

private:
    vector<Email> emails;

    void displayEmail(const Email & email) const {
        cout << "From: " << email.getSender() << "\n";
        cout << "Subject: " << email.getSubject() << "\n";
        cout << "Body: " << email.getBody() << "\n";
    }

public:
    void receiveEmail(const Email& email) {
        emails.push_back(email);
    }

    void displayUnreadEmails() const {
        cout << "Unread Emails in Inbox:\n";
        for (size_t i = 0; i < emails.size(); ++i) {
            if (!emails[i].isRead()) {
                displayEmail(emails[i]);
                cout << "Index: " << i << "\n\n";
            }
        }
    }

    void markEmailAsRead(int index) {
        if (index >= 0 && static_cast<size_t>(index) < emails.size()) {
            emails[index].markAsRead();
            cout << "Email marked as read.\n";
        } else {
            cout << "Invalid email index.\n";
        }
    }


};

class Outbox {

private:
    vector<Email> sentEmails;

    void displayEmail(const Email& email) const {
        cout << "To: " << email.getSender() << "\n";
        cout << "Subject: " << email.getSubject() << "\n";
        cout << "Body: " << email.getBody() << "\n";
    }

public:
    void sendEmail(const Email& email, Inbox& recipientInbox) {
        recipientInbox.receiveEmail(email);
        sentEmails.push_back(email);
        cout << "Email sent successfully.\n";
    }

    Email composeEmail() const {
        string recipient, subject, body;
        cout << "Enter recipient email address: ";
        cin >> recipient;
        cin.ignore(); // Ignore the newline character

        cout << "Enter email subject: ";
        getline(cin, subject);

        cout << "Enter email body: ";
        getline(cin, body);

        return Email(recipient, subject, body);
    }

    void displaySentEmails() const {
        cout << "Sent Emails:\n";
        for (size_t i = 0; i < sentEmails.size(); ++i) {
            displayEmail(sentEmails[i]);
        }
    }


};

int main() {
    Inbox myInbox;
    Outbox myOutbox;

    int choice = 0;
    while (choice != 5) {
        cout << "Email Client Menu:\n";
        cout << "1. Compose and Send Email\n";
        cout << "2. Display Unread Emails\n";
        cout << "3. Mark Email as Read\n";
        cout << "4. Display Sent Emails\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Email newEmail = myOutbox.composeEmail();
                myOutbox.sendEmail(newEmail, myInbox);
                break;
            }
            case 2:
                myInbox.displayUnreadEmails();
                break;
            case 3: {
                int index;
                cout << "Enter the index of the email to mark as read: ";
                cin >> index;
                myInbox.markEmailAsRead(index);
                break;
            }
            case 4:
                myOutbox.displaySentEmails();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    }

    return 0;
}