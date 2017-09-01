#include <string>
#include <yatbcpp/yatbcpp.h>

yatbcpp::Token token("replace me with a usefull token");
yatbcpp::Bot B(token);

/**
 * Simple callback to say hello world or if it knows the user hello [first name]
 * @param M the Message which the callback will get
 */
void update_callback(yatbcpp::Message M){
    using namespace std;
    using namespace yatbcpp;
    string message= "Hello " ;

    if( M.getFrom() ){
        message += M.getFrom().value().getFirst_name();
    }
    else{
        message += "World";
    }
    auto gm = yatbcpp::getMe();
    auto Usr = yatbcpp::getMe::perform_requestJSON(token,gm);
    sendMessage sendMessage(M.getChat(),message);
    telegram_methodJSON<yatbcpp::Message>::perform_requestJSON(token,sendMessage);

}



int main() {
    using namespace yatbcpp;
    //Getting The Bot as User from the GetMe Function
    User U = B.getMe();
    //Adding our onMessageListener
    B.addOnMessageListener(update_callback);
    //Starting the update queue for incoming or pending updates
    B.startUpdating();
    //Starting the poll for updates
    B.startLongPoll();
    //Waiting to join the thread
    B.join();
    return 0;
}
