#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include <fstream>

class Subject {
private:
    std::string text_;
    std::string filename_;

public:
    Subject(const std::string& filename);

    std::string getText();
    void setText(const std::string& text);
    std::string getFilename();

    void replaceWord(const std::string& target, const std::string& replacement);
    bool findPhrase(const std::string& phrase);
    void capitalizeWords();
    void capitalizeSentences();
    std::string getNumberedSentences();

    bool saveToFile();
    bool saveTextToFile(const std::string& text, const std::string& outputFilename);
};

#endif