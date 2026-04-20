#include <nn/ssl/ssl_LibManager.h>
namespace nn{
namespace ssl{
namespace detail{
LibManager::~LibManager(){
    this->mHandleObj.Close();
}

}
}
}