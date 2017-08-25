#include <string>
#include <yatbcpp/yatbcpp.h>


yatbcpp::Token token("replace me with a usefull token");
yatbcpp::Bot B(token);

/**
 * Simple callback to say hello world or if it knows the user hello [first name]
 * @param M the Message which the callback will get
 */
void update_callback(yatbcpp::Message M){
    std::string message= "Hello " ;
    if( M.getFrom() ){
        message += M.getFrom().value().getFirst_name();
    }
    else{
        message += "World";
    }
    yatbcpp::sendMessage sendMessage(M.getChat(),message);
    B.send(sendMessage);
}

int main() {
    using namespace yatbcpp;

    B.addOnMessageListener(update_callback);

    B.startUpdating();
    B.startLongPoll();

    B.join();
    return 0;
}