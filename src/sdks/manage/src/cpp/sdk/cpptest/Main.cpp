#include <getopt.h>
#include "ManageSDKTest.h"

void ShowMenu()
{
    printf("Options ---- >\n"
           "\tG : AcknowledgeChallenge Provider\n"
           "\tO : Account\n"
           "\tA : Advertising\n"
           "\tE : AudioDescriptions\n"
           "\tC : ClosedCaption\n"
           "\tD : Device\n"
           "\tI : Discovery\n"
           "\tK : Keyboard Provider\n"
           "\tL : Localization\n"
           "\tP : PinChallenge Provider\n"
           "\tV : Privacy\n"
           "\tU : UserGrant\n"
           "\tW : Wifi\n"
           "\tQ : Quit\n\n"
          );
}

void ShowAccountMenu()
{
    printf("Options \n"
         "\tS : Set Account Session\n"
         "\tQ : Quit\n");
}

void ShowAdvertisingMenu()
{
    printf("Options \n"
         "\tS : Get/Set Advertising skipRestriction\n"
         "\tR : Reset Advertising Identifier\n"
         "\tQ : Quit\n");
}

void ShowAudioDescriptionsMenu()
{
   printf("Options \n"
         "\tA : Get/Set/Subscribe/Unsubscribe AudioDescriptions Enabled\n"
         "\tQ : Quit\n");
}

void ShowClosedCaptionsMenu()
{
   printf("Options \n"
         "\tB : Get/Set/Subscribe/Unsubscribe ClosedCaption Background Opacity\n"
         "\tF : Get/Set/Subscribe/Unsubscribe ClosedCaption Font Family\n"
         "\tQ : Quit\n");
}

void ShowDeviceMenu()
{
   printf("Options \n"
         "\tN : Get/Set/Subscribe/Unsubscribe Device Name\n"
         "\tQ : Quit\n");
}

void ShowDiscoveryMenu()
{
   printf("Options \n"
         "\tI : Subscribe/Unsubscribe SignIn notification\n"
         "\tO : Subscribe/Unsubscribe SignOut notification\n"
         "\tQ : Quit\n");
}

void ShowAdditionalInfoMenu()
{
    printf("Options \n"
         "\tG : Get Additional Info\n"
         "\tA : Add Additional Info\n"
         "\tR : Remove Additional Info\n"
         "\tQ : Quit\n");
}

void ShowLocalizationMenu()
{
   printf("Options \n"
         "\tD : Operate on Localization Additional Info\n"
         "\tP : Get/Set/Subscribe/Unsubscribe Localization Preferred AudioLanguages\n"
         "\tQ : Quit\n");
}

void ShowPrivacyMenu()
{
   printf("Options \n"
         "\tA : Get/Set/Subscribe/Unsubscribe Privacy Allow ACR Collection\n"
         "\tS : Get Privacy Settings\n"
         "\tQ : Quit\n");
}

void ShowUserGrantsMenu()
{
    printf("Invoke lifecyclesession management sequence from postman \n"
         "Once the permission granted/denies/cleared, please use provider + api test to validate it \n"
         "Here capabilty used for the testing is hardcoded as device:model\n"
         "\tG : Get Permission\n"
         "\tR : Grant Permission\n"
         "\tD : Deny Permission\n"
         "\tC : Clear Permission\n"
         "\tQ : Quit\n");
}

void ShowWifiOperationsMenu()
{
    printf("Options \n"
         "\tS : Scan access points\n"
         "\tC : Connect to selected access point \n"
         "\tD : Disconnect from access point \n"
         "\tQ : Quit\n");
}

void ShowPropertyMenu(std::string& module, std::string& property)
{
    printf("%s:%s property options \n"
         "\tG : Get value\n"
         "\tS : Set value\n"
         "\tQ : Quit\n", module.c_str(), property.c_str());
}

void ShowPropertyWithEventMenu(std::string& module, std::string& property)
{
    printf("%s:%s property options \n"
         "\tG : Get value\n"
         "\tS : Set value\n"
         "\tR : Show subscribe/unscribe event menu\n"
         "\tQ : Quit\n", module.c_str(), property.c_str());
}

void ShowProviderMenu(std::string& module)
{
    printf("Invoke lifecyclesession management from postman and api sequence from other entity for %s and press\n"
         "\tR : To Send Response\n"
         "\tE : To Send Error\n"
         "\tQ : Quit\n", module.c_str());
}

void ShowEventMenu()
{
    printf("Options \n"
         "\tS : Subscribe Event\n"
         "\tU : Unsubscribe Event\n"
         "\tQ : Quit\n");
}

#define VALUE(string) #string
#define TO_STRING(string) VALUE(string)

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

#define HandleProperty(Module, Property) \
{ \
    int opt; \
    do { \
        getchar(); \
        std::string module = TO_STRING(Module); \
        std::string property = TO_STRING(Property); \
        ShowPropertyMenu(module, property); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'G': { \
            ManageSDKTest::Get##Module##Property(); \
            break; \
        } \
        case 'S': { \
            ManageSDKTest::Set##Module##Property(); \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
}

#define HandlePropertyWithEvent(Module, Property) \
{ \
    int opt; \
    do { \
        getchar(); \
        std::string module = TO_STRING(Module); \
        std::string property = TO_STRING(Property); \
        ShowPropertyWithEventMenu(module, property); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'G': { \
            ManageSDKTest::Get##Module##Property(); \
            break; \
        } \
        case 'S': { \
            ManageSDKTest::Set##Module##Property(); \
            break; \
        } \
        case 'R': { \
            HandleEventListener(Module, Property##Changed) \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
}

#define HandleProviderSequence(Module) \
{ \
    int opt; \
    do { \
        getchar(); \
        std::string module = TO_STRING(Module); \
        ShowProviderMenu(module); \
        printf("Enter option : "); \
        opt = toupper(getchar()); \
        switch (opt) { \
        case 'R': { \
            ManageSDKTest::SendResponseMessageTo##Module##Provider(); \
            break; \
        } \
        case 'E': { \
            ManageSDKTest::SendErrorMessageTo##Module##Provider(); \
            break; \
        } \
        default: \
            break; \
        } \
    } while (opt != 'Q'); \
}

void HandleAccountMethods()
{
    int opt;
    do {
        getchar();
        ShowAccountMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'S': {
            ManageSDKTest::SetAccountSession();
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleAdvertisingMethods()
{
    int opt;
    do {
        getchar();
        ShowAdvertisingMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'S': {
            HandleProperty(Advertising, SkipRestriction)
            break;
        }
        case 'R': {
            ManageSDKTest::ResetAdvertisingIdentifier();
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleAudioDescriptionsMethods()
{
    int opt;
    do {
        getchar();
        ShowAudioDescriptionsMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'A': {
            HandlePropertyWithEvent(AudioDescriptions, Enabled)
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleClosedCaptionsMethods()
{
    int opt;
    do {
        getchar();
        ShowClosedCaptionsMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'B': {
            HandlePropertyWithEvent(ClosedCaptions, BackgroundOpacity)
            break;
        }
        case 'F': {
            HandlePropertyWithEvent(ClosedCaptions, FontFamily)
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleDeviceMethods()
{
    int opt;
    do {
        getchar();
        ShowDeviceMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'N': {
            HandlePropertyWithEvent(Device, Name)
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleDiscoveryMethods()
{
    int opt;
    do {
        getchar();
        ShowDiscoveryMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'I': {
            HandleEventListener(Discovery, SignInNotification)
            break;
        }
        case 'O': {
            HandleEventListener(Discovery, SignOutNotification)
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleAdditionalInfo()
{
    int opt;
    do {
        getchar();
        ShowAdditionalInfoMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'G': {
            ManageSDKTest::GetLocalizationAdditionalInfo();
            break;
        }
        case 'A': {
            ManageSDKTest::AddLocalizationAdditionalInfo();
            break;
        }
        case 'R': {
            ManageSDKTest::RemoveLocalizationAdditionalInfo();
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleLocalizationMethods()
{
    int opt;
    do {
        getchar();
        ShowLocalizationMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'D': {
            HandleAdditionalInfo();
            break;
        }
        case 'P': {
            HandlePropertyWithEvent(Localization, PreferredAudioLanguages)
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandlePrivacyMethods()
{
    int opt;
    do {
        getchar();
        ShowPrivacyMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'A': {
            HandlePropertyWithEvent(Privacy, AllowACRCollection)
            break;
        }
        case 'S': {
            ManageSDKTest::GetPrivacySettings();
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleUserGrants()
{
    int opt;
    do {
        getchar();
        ShowUserGrantsMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'G': {
            ManageSDKTest::GetUserGrantsPermission();
            break;
        }
        case 'R': {
            ManageSDKTest::GrantUserGrantsPermission();
            break;
        }
        case 'D': {
            ManageSDKTest::DenyUserGrantsPermission();
            break;
        }
        case 'C': {
            ManageSDKTest::ClearUserGrantsPermission();
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

void HandleWifiOperations()
{
    int opt;
    do {
        getchar();
        ShowWifiOperationsMenu();
        printf("Enter option : ");
        opt = toupper(getchar());
        switch (opt) {
        case 'S': {
            ManageSDKTest::WifiScan();
            break;
        }
        case 'C': {
            ManageSDKTest::WifiConnect();
            break;
        }
        case 'D': {
            ManageSDKTest::WifiDisconnect(); // This method is not avaialble from ripple now
            break;
        }
        default:
            break;
        }
    } while (opt != 'Q');
}

#define options ":hu:"
int main (int argc, char* argv[])
{
    int c;
    std::string url = "ws://127.0.0.1:9998";
    while ((c = getopt (argc, argv, options)) != -1) {
        switch (c)
        {
            case 'u':
                 url = optarg;
                 break;

            case 'h':
                 printf("./TestFireboltManage -u ws://ip:port\n");
                 exit(1);
        }
    }

    printf("Firebolt Manage SDK Test\n");
    ManageSDKTest::CreateFireboltInstance(url);
    int option;

    if (ManageSDKTest::WaitOnConnectionReady() == true) {
       do {
            ShowMenu();
            printf("Enter option : ");
            option = toupper(getchar());
            switch (option) {
            case 'O': {
                HandleAccountMethods();
                break;
            }
            case 'A': {
                HandleAdvertisingMethods();
                break;
            }
            case 'E': {
                HandleAudioDescriptionsMethods();
                break;
            }
            case 'C': {
                HandleClosedCaptionsMethods();
                break;
            }
            case 'D': {
                HandleDeviceMethods();
                break;
            }
            case 'I': {
                HandleDiscoveryMethods();
                break;
            }
            case 'K': {
                ManageSDKTest::RegisterKeyboardProvider();
                HandleProviderSequence(Keyboard)
                break;
            }
            case 'G': {
                ManageSDKTest::RegisterAcknowledgeChallengeProvider();
                HandleProviderSequence(AcknowledgeChallenge)
                break;
            }
            case 'P': {
                ManageSDKTest::RegisterPinChallengeProvider();
                HandleProviderSequence(PinChallenge)
                break;
            }
            case 'L': {
                HandleLocalizationMethods();
                break;
            }
            case 'V': {
                HandlePrivacyMethods();
                break;
            }
            case 'U': {
                HandleUserGrants();
                break;
            }
            case 'W': {
                HandleWifiOperations();
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
