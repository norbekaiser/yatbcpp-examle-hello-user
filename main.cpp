#include <string>
#include <yatbcpp/yatbcpp.h>

yatbcpp::Token token("replace me with a usefull token");

yatbcpp::Bot B(token);

/**
 * Callback to print out the botsname on each message
 * @param M the received message
 */
void print_selfname_callback(yatbcpp::Message M){
    using namespace yatbcpp;
    using namespace std;
    //The GetMe Message Body
    auto gm = getMe();
    //Performing the Request without using a bot
    auto Usr = getMe::perform_requestJSON(token,gm);

    cout << "Bot Username:" << Usr << endl;
}


/**
 * Simple callback to say hello world or if it knows the user hello [first name]
 * @param M the Message which the callback will get
 */
void update_callback(yatbcpp::Message M){
    using namespace std;
    using namespace yatbcpp;

    string message= "Hello " ;
//    string message= "Bonjour " ;
//    string message= "Guten Tag " ;

    if( M.getFrom() ){
        message += M.getFrom().value().getFirst_name();
    }
    else{
        message += "World";

    }

    //Message Body Preparation
    sendMessage sendMessage(M.getChat(),message);
    //Sending the Message
    telegram_methodJSON<yatbcpp::Message>::perform_requestJSON(token,sendMessage);

    //Optionally Send a photo stored as ./botphoto.jpg
    //Multi part request, will handle the string as a path and use the multipart message to send the file
    //    sendPhoto sendPhoto(M.getChat(),"./botphoto.jpg");
    //    telegram_methodMultipart<yatbcpp::Message>::perform_requestMultipart(token,sendPhoto); //local path
    //    telegram_methodMultipart<yatbcpp::Message>::perform_requestJSON(token,sendPhoto); //media id or web path
    // This Example supplys a web path and sends it via the json methods
    sendPhoto sendPhoto(M.getChat(),"https://norbco.de/wp-content/uploads/2015/06/wpid-20150612_080104.jpg");
    sendPhoto::perform_requestJSON(token,sendPhoto);

    //However you can also send preexisting media by supplying the id , beware that the media must be known to the bot
    //    sendVoice sendVoice(M.getChat(),"REPLACE_ME_WITH_MEDIA_ID");
    //    sendVoice::perform_requestJSON(token,sendVoice); //Media id or web path
    //    sendVoice::perform_requestMultipart(token,sendVoice); // local path





}

/**
 * the Bot library is particulary capable of answering inline queries
 * @param I the InlineQuery
 */
void inline_callback(yatbcpp::InlineQuery I){
    using namespace yatbcpp;
    using namespace std;
    cout << "Inline Query Received" << endl;
    cout <<  I.getQuery() << endl;
    //Verify that the Inline Query contains "Hello"
    if(I.getQuery().find("Hello")!=string::npos) {

        //And answer it with a direct message at first?
        sendMessage message(I.getFrom().getId(), "Hello " + I.getFrom().getFirst_name() + "\nTry lorem");

        telegram_methodJSON<yatbcpp::Message>::perform_requestJSON(token, message);
    }
    if(I.getQuery().find("lorem")!=string::npos) {
//        https://core.telegram.org/bots/api#inlinequeryresult
        //Try it yourself, send a voice sample to the bot, retrieve the media id and replace it
//        InlineQueryResultCachedVoice inlineQueryResultCachedVoice("1","REPLACE_ME_WITH_A_VOICE_MEDIA_ID","ipsum dolor sit ament");
//        std::vector<InlineQueryResult*> results;
//        results.push_back(&inlineQueryResultCachedVoice);
//        Up to 50 Results may be returned
//        answerInlineQuery answerInlineQuery(I.getId(),results);
//        bool x = telegram_simplemethodJSON::perform_simplerequestJSON(token,answerInlineQuery);
    }







}



int main() {
    using namespace yatbcpp;
    //Getting The Bot as User from the GetMe Function
    //    User U = B.getMe();
    //Adding our onMessageListener
    B.addOnMessageListener(update_callback);
    B.addOnMessageListener(print_selfname_callback);
    B.addOnInlineQueryListener(inline_callback);
    //Starting the update queue for incoming or pending updates
    B.startUpdating();
    //Starting the poll for updates
    B.startLongPoll();
    //Waiting to join the thread
    B.join();
    return 0;
}
