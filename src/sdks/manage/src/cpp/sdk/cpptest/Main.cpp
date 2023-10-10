
#include "ManageSDKTest.h"

void ShowMenu()
{
    printf("Enter\n"
           "\tN : Get Device Name\n"
           "\tS : Set Device Name\n"
           "\tC : Subscribe/Unsubscribe for Device Name Change\n"
           "\tB : Get ClosedCaption Background Opacity\n"
           "\tO : Set ClosedCaption Background Opacity\n"
           "\tF : Get ClosedCaption Font Family\n"
           "\tM : Set ClosedCaption Font Family\n"
           "\tL : Get Localization Preferred AudioLanguages\n"
           "\tP : Set Localization Preferred AudioLanguages\n"
           "\tQ : Quit\n\n"
          );
}

void ShowEventMenu()
{
    printf("Enter\n"
         "\tS: Subscribe Event\n"
         "\tU: Unsubscribe Event\n"
         "\tQ : Quit\n");
}

#define HandleEventListener(Module, eventFuncName) \
{ \
    int opt; \
    do { \
        getchar(); \
        ShowEventMenu(); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'S': { \
            ManageSDKTest::Subscribe##Module##eventFuncName(); \
            break; \
        } \
        case 'U': { \
            ManageSDKTest::Unsubscribe##Module##eventFuncName(); \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
}

int main (int argc, char* argv[])
{
    char* config = "{\
    \"waitTime\": 1000,\
    \"logLevel\": \"Info\",\
    \"workerPool\":{\
        \"queueSize\": 8,\
        \"threadCount\": 3\
    },\
    \"wsUrl\": \"ws://127.0.0.1:9998\"\
}";

    printf("Firebolt Manage SDK Test\n");
    
    ManageSDKTest::CreateFireboltInstance();
    int option;

    if (ManageSDKTest::WaitOnConnectionReady() == true) {
       do {
            ShowMenu();
            printf("Enter option : ");
            option = toupper(getchar());
            switch (option) {
            case 'N': {
                ManageSDKTest::GetDeviceName();
                break;
            }
            case 'S': {
                ManageSDKTest::SetDeviceName();
                break;
            }
            case 'C': {
                HandleEventListener(Device, NameChanged)
                break;
            }
            case 'B': {
                ManageSDKTest::GetClosedCaptionBackgroundOpacity();
                break;
            }
            case 'O': {
                ManageSDKTest::SetClosedCaptionBackgroundOpacity();
                break;
            }
            case 'F': {
                ManageSDKTest::GetClosedCaptionFontFamily();
                break;
            }
            case 'M': {
                ManageSDKTest::SetClosedCaptionFontFamily();
                break;
            }
            case 'L': {
                ManageSDKTest::GetLocalizationPreferredAudioLanguages();
                break;
            }
            case 'P': {
                ManageSDKTest::SetLocalizationPreferredAudioLanguages();
                break;
            }

            default:
                break;
            }
            getchar(); // Skip white space
        } while (option != 'Q');

    } else {
        printf("Manage Test not able to connect with server.... \n");
    }

    ManageSDKTest::DestroyFireboltInstance();

    return 0;
}
