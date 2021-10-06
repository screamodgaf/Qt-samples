/*  DOCUMENTATION:
 *  first use use goIntoTag(std::string html, std::string int tagCounter),
 *  - to display content of all the occurences of the choisen tag - by using loop in main;
 *
 *  alternative to goIntoTag() but returns a vector - thus faster
 *  std::vector<std::string>findAllTags(std::string text, std::string tag_)
 *
 *
 *  then use extract_tagContent(std::string, std::string tag )
 *  Tags to use:
 *  simple tag ex. <a> - write as "a"
 *  tag with arguments ex. <div href= ...> - write as "div " (with space after tag)
 *  std::string tag = "div "; //with space after tag
 *
 *
 *  extract_link(std::string text) - extracts link from <a href="www.something.com">
 *
 *
 *  EXAMPLE of using tag with arguments:
 *  ex. text = "lalala <div href=\"/225398-we-wloszech-uczczono-zolnierzy-"
 *         "gen-andersa\">We Włoszech uczczono żołnierzy gen. Andersa</div> lalala";
 *  tag = "div ";
 *
 *  WORKING USAGE EXAMPLE:
 *  std::string inTagCalosc2 = parser.goIntoTag(inTagCalosc, "li wdq", 0);
 *  std::string inTagCalosc3 = parser.extract_tagContent(inTagCalosc2, "a " );
 *  -------------------------------------------------------
 *
 *   for (int var = 0; var <= 0; ++var)
 *   {
 *       std::string newText = parser.goIntoTag(text, "span class=\"entry-title\"",var);
 *       std::string newText2 = parser.extract_tagContent(newText, "a ");
 *       std::cout << newText2  << "\n";
 *       std::string newText3 = parser.extract_link(newText);
 *       std::cout << newText3  << "\n";
 *   }
 *  ------------------------------------------
 *  to extract from different tags use:
 *  extractFromDifferentTags(std::string tagFirst, std::string tagLast, std::string text)
 *  for ex: parser.extractFromDifferentTags("/a", "/p",newText);
 *  ------------------------------------------
 *
 *  arbitrary choisen words
 *  std::string text = "aaa<meta name=\"keywords\" content=\"Chill Synthwave Mix, Chill Wave 2021, Study Relax, Retrowave Mix, retrowave, synthwave mix, retrowave mix, chillwave mix, chill synthwave, synthwave, chillwave, chillwave music, chillwave music 2020, ambient chillwave music, 80s, synthwave music, synthwave music mix, best of synthwave music mix, cyberpunk music, cyberpunk music mix, cyberpunk mix, ambient music, chillwave ambient, 80s music, retro electro music, future music, &#39;Back To The 80&#39;s&#39; 2021, VavoWaveRelax\"> bbb";
 *  std::string begTag = "<meta name=\"keywords\" content=\"";
 *  std::string endTag = "\">";
 *  std::cout << "findYoutubeKeywords: " << findYoutubeKeywords(begTag, endTag, text) << "\n";

 */

#include "parser.h"

Parser::Parser()
{

}

std::string Parser::extract_tagContent(std::string text , std::string tag_)
{
    if(tag_.find(" ")!=std::string::npos)
    {
        std::string tag = tag_;
        size_t spacePosInFirstTag = tag.find(" ");
        std::string tagCore  = tag.substr(0, spacePosInFirstTag ); //<a href>
        std::string tagClosing = "</"+tagCore+ ">";

        size_t tagClosingPos = text.find(tagClosing);


        size_t tagFirstFound = text.find(tag);
        size_t post_FirstTagPos = text.find(">", tagFirstFound)+1 ;

        std::string textInTags;
        textInTags = text.substr(post_FirstTagPos, tagClosingPos-post_FirstTagPos);


        return textInTags;
    }
    else //if the tag is without space in it, it's simple like <a> or <li> so on
    {
        std::string tag = tag_;
        tag = "<" +tag + ">";
        size_t tagPos;
        tagPos=text.find(tag);
        size_t post_tagPos;
        post_tagPos = tagPos+tag.length();

        std::string tagClosing = "</" +tag_ + ">";
        size_t tagClosingPos;
        tagClosingPos = text.find(tagClosing, post_tagPos);

        std::string textInTags;
        textInTags = text.substr(post_tagPos, tagClosingPos-post_tagPos);

        return textInTags;
    }
}


void Parser::count_Tags(std::string text_, std::string tag_)
{

    std::string tag = tag_;
    std::string text =text_;

    size_t countOfTagApprc =0;
    size_t moveToNext=0;
    for(auto i=0; i<text.length(); i++)
    {
        if(text.find("<"+tag, moveToNext)!=std::string::npos)
        {
            moveToNext = text.find("<"+tag, moveToNext);
            //std::cout<< "position of last occurence: " << moveToNext << "\n";
            countOfTagApprc++;
            moveToNext++;
        }

    }
    std::cout<< "countOfTagApprc: " << countOfTagApprc << "\n";
}

void Parser::moveToNode(std::string text_, std::string tag_, std::string tag_value_)
{//class
    std::string tag = tag_;
    std::string tag_value = tag_value_;
    std::string text =text_;

    //fill="#FFFFFF"
    //class="clear"
}

//for displying all choisen tag content:
std::vector<std::string> Parser::list_allTags(std::string text_, std::string tag_)
{
    const std::string tag = "<"+tag_+">";;
    int tagCount=0;
    std::string text =text_;
    const std::string tagClose = "</ul>";
    std::map<int, std::string>map;
    int tagBeginingPosition;
    int tagClosePosition;
    int loopToNextTagPosition =0;

    std::vector<std::string> textInDefinedTag;
    for(auto i =0; i<text.length(); i++)
    {
        if(text.find(tag,loopToNextTagPosition)!=std::string::npos )
        {
            tagBeginingPosition = text.find(tag, loopToNextTagPosition);
            //std::cout<<"\n" << "tagBeginingPosition: " << tagBeginingPosition <<"\n";
            tagClosePosition = text.find(tagClose, tagBeginingPosition+tag.length());
            //std::cout<<"\n" <<"tagClosePosition: " << tagClosePosition <<"\n";
            std::string temp = text.substr(tagBeginingPosition+tag.length(), tagClosePosition-(tagBeginingPosition+tag.length()));
            textInDefinedTag.push_back(temp);
            std::cout<<"\n" << temp <<"\n";

            loopToNextTagPosition=tagClosePosition;
            tagBeginingPosition++;
        }
    }
    return textInDefinedTag;
}



//for displying specific tag content:
std::string Parser::goIntoTag(std::string text_, std::string tag_, int requiredTagCount_)
{
    const std::string tag = "<"+tag_+">"; //<span>
    int requiredTagCount = requiredTagCount_;
    int tagCount=0;
    std::string text =text_;
    std::string tagClose;
    if(tag.find(" ")==std::string::npos)//tag has no space
    {
        tagClose = "</"+tag_+">";
        //std::cout << "TAG CLOSE - no space: " << tagClose << "\n";
    }
    else// if there is space
    {
        size_t space = tag.find(" ");
        tagClose = tag.substr(1,space-1);
        tagClose = "</"+ tagClose +">";
        //std::cout << tagClose << "\n";;
    }



    size_t tagBeginingPosition;
    size_t tagClosePosition;
    size_t loopToNextTagPosition =0;
//cel - tag niezlaneziony wiec loopToNextTagPosition musi sie powiekszac
    std::vector<std::string> textInDefinedTag;
    while(tagClosePosition  !=std::string::npos )
    {
        tagBeginingPosition=text.find(tag,loopToNextTagPosition); //  <span>
        tagClosePosition = text.find(tagClose,tagBeginingPosition); //  </span>
        std::string temp = text.substr(tagBeginingPosition+tag.length(),
                                       tagClosePosition- (tagBeginingPosition+tag.length()));
        textInDefinedTag.push_back(temp);
        //std::cout<<"TEMPPP" << temp <<"\n";

        loopToNextTagPosition=tagClosePosition;
        tagBeginingPosition++;
        tagCount++;
    }

    if(requiredTagCount<=tagCount)
    {//@@@@ display
        //std::cout<<"\n" << textInDefinedTag[requiredTagCount] <<"\n";
        return textInDefinedTag[requiredTagCount]; //returns vector<string>
    }
    else
    {
        std::cout<<"\n" << "requiredTagCount is too big" <<"\n";
        return "requiredTagCount is too big";

    }
}

std::string Parser::extract_link(std::string text)
{
    size_t foundQuote;
    size_t foundQuote2;
    std::string subText;
    if(( foundQuote =(text.find("\"")))!=std::string::npos &&
       (foundQuote2 =(text.find("\"", foundQuote+1)))!=std::string::npos)
    {
        subText = text.substr(foundQuote+1, foundQuote2-(foundQuote+1));
        //std::cout << "foundQuote: " <<foundQuote << "\n";
        //std::cout << "foundQuote2: " <<foundQuote2 << "\n";
        //std::cout << subText << "\n";
    }
    return subText;
}

std::string Parser::extractFromDifferentTags(std::string tagFirst, std::string tagLast, std::string text)
{
    size_t tagFirstPos;
    size_t tagLastPos;
    std::string result;
    if((tagFirstPos=text.find(tagFirst))!=std::string::npos &&
       (tagLastPos=text.find(tagLast))!=std::string::npos)
    {
         size_t textBeginning =  tagFirstPos+ tagFirst.length() ;
         size_t textEnd = tagLastPos;

         result = text.substr(textBeginning+1 , (textEnd-1)-(textBeginning+1));

        //std::cout << result << "\n";
    }
    return result;
}


//alternative to goIntoTag() but returns a vector
std::vector<std::string>Parser::findAllTags(std::string text, std::string tag_)
{
    std::vector <std::string> lines;
    if(tag_.find(" ")==std::string::npos)//simple <a> or <li>
    {
        std::string tag = tag_;
        tag = "<" +tag + ">"; //<a>
        size_t jumpLoop = 0;
        size_t tagFirstPos;
        size_t tagClosePos;
        std::string tagClosing= "</" +tag_ + ">";

        while((tagFirstPos=text.find(tag, jumpLoop))!=std::string::npos &&
              (tagClosePos=text.find(tagClosing, tagFirstPos))!=std::string::npos)
        {
            size_t post_tagPos;
            post_tagPos = tagFirstPos+tag.length();

            std::string textInTags;
            textInTags = text.substr(post_tagPos, tagClosePos-post_tagPos);
            lines.push_back(textInTags);

            jumpLoop=tagClosePos+1;
        }

        return lines;
    }
    else //if there is space in tag <a href>
    {
        std::string tag = tag_;
        size_t spacePosInFirstTag = tag.find(" ");
        std::string tagCore  = tag.substr(0, spacePosInFirstTag ); //<a href>
        std::string tagClosing = "</"+tagCore+ ">";

        size_t tagFound;
        size_t tagClosingBracket;
        tagFound = text.find(tag_);//to eliminate this find() id need to give whole tag info "a href"
        tagClosingBracket = text.find(">", spacePosInFirstTag);

        tag  = "<" + text.substr(tagFound, (tagClosingBracket+1)-tagFound);
        //std::cout << "tag: " << tag   << "\n";


        size_t jumpLoop =0;
        size_t tagFirstPos;
        size_t tagClosePos;


        while((tagFirstPos=text.find(tag, jumpLoop))!=std::string::npos &&
              (tagClosePos=text.find(tagClosing, tagFirstPos))!=std::string::npos)
        {
            size_t post_tagPos;
            post_tagPos = tagFirstPos+tag.length();

            std::string textInTags;
            textInTags = text.substr(post_tagPos, tagClosePos-post_tagPos);
            lines.push_back(textInTags);

            jumpLoop=tagClosePos+1;
        }

        return lines;
    }

}

std::string Parser::findYoutubeKeywords(std::string begTag, std::string endTag, std::string text)
{
    size_t begTagSize = begTag.size();
    if(begTagSize == 0)
        std::cout << "ERROR: begTagSize == 0" << "\n";
    //    size_t beg = text.find(begTag);
    //    size_t end = text.find(endTag,beg);

    size_t beg;
    if((beg = text.find(begTag))==std::string::npos)
        std::cout << "ERROR: begTag not found" << "\n";

    size_t end;
    if((end =  text.find(endTag,beg))==std::string::npos)
        std::cout << "ERROR: endTag not found" << "\n";

    std::string substring =  text.substr(beg+begTagSize, end - (beg+begTagSize));
    //std::cout << substring << "\n";
    return substring;
}


std::string Parser::limitKeysLength(std::string& text, size_t lengthLimit)
{
    std::string result ="";
    size_t beg0 = 0;
    size_t beg1 = 0;
    size_t prev = 0;
    size_t end = text.size();
    std::string lastKey;
    while ((beg1 = text.find(",",beg0))!=std::string::npos) {
        if(beg1>lengthLimit){
            end = lengthLimit;
            break;
        }
        //std::cout << "prev: " << prev  <<", beg1: " << beg1 << "\n";
        std::string keys = text.substr(prev, beg1-prev);
        prev = beg1+2 ;
        beg0 = ++beg1;
        std::cout << keys << "\n";
        result+= (keys + ", ");
    }
    //std::cout << "prev: " << prev  <<", beg1: " << beg1 << "\n";
    if(prev==0) return "";


    if(beg1<=end){
        // std::cout << "added" << "\n";
        lastKey = text.substr(prev, end-prev);
        result+=lastKey;
    }

    size_t size = result.size();
    if(result[size-1] == ' '){
        std::cout << "if(result[size-1] == ',')" << "\n";
        result.resize(result.size()-2);
    }

    return result;
}
