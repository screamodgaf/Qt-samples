#ifndef PARSER_H
#define PARSER_H
#include <QObject>
#include <iostream>
#include <string>
#include <fstream>
#include <QDebug>
#include <sstream>
#include <vector>


class Parser
{
public:
Parser();
int x;
std::string extract_tagContent(std::string text, std::string tag_);
void count_Tags(std::string text_, std::string tag_);
void moveToNode(std::string text_, std::string tag_, std::string tag_value_);
std::vector<std::string> list_allTags(std::string text_, std::string tag_);
std::string goIntoTag(std::string text_, std::string tag_, int requiredTagCount_);
std::string extract_link(std::string text);
std::string extractFromDifferentTags(std::string tagFirst, std::string tagLast, std::string text);
std::vector<std::string>findAllTags(std::string text, std::string tag_);
std::string findYoutubeKeywords(std::string begTag, std::string endTag, std::string text);

std::string limitKeysLength(std::string& text, size_t lengthLimit);
};

#endif // PARSER_H
