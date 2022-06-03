#include <iostream>
#include <string>

class Text {
public:
    virtual void setContent(std::string* content) {}
    virtual std::string getContent() = 0;
    virtual Text* clone() const = 0;
};

class TermPaper : public Text {
private:
    std::string* content;
    TermPaper(const TermPaper& donor) {
        this->content = donor.content;
    }

public:
    TermPaper() {};
    ~TermPaper() {
        delete content;
    }

    void setContent(std::string* content) override {
        this->content = content;
    }

    std::string getContent() override {
        return *content;
    }

    TermPaper* clone() const {
        return new TermPaper(*this);
    }
};

int main() {
    TermPaper* termPaperDonor = new TermPaper();
    std::string content = "Very interesting content";
    termPaperDonor->setContent(&content);

    TermPaper* termPaperClone = termPaperDonor->clone();

    std::cout << termPaperDonor->getContent() << std::endl;
    std::cout << termPaperClone->getContent() << std::endl;
}