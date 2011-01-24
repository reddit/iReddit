
// ReadItLaterLite.h
// Basic methods for custom interaction with the RIL API


/* ---------
 
 PLEASE READ:
 
 The ReadItLaterLite Class provides very basic methods to save, login, and register.  
 They should be used if you'd like to manage your own UI for interacting with Read It Later.
 Using this class you will need to create the displays/forms associated with adding RIL support.
 
 If you'd like a more drop in solution where loading screens and login forms are displayed for you,
 take a look at the optional ReadItLaterFull class.  The Full class can be used to add full RIL support
 to your app by adding less than 3 lines of code.
 
 -------------- */


/* --- For some examples of how to use this, see http://readitlaterlist.com/api_iphone/ or view the ReadItLaterFull class which implements all of these functions -- */


// ReadItLaterDelegate Protocol - Handles responses from the API:

// stringResponse	will be the actual data returned from the API, you only need to look at this if
//					you are using methods like 'get' that return data

// errorString		if it's nil, the call was successful. Otherwise it will contain a string with a message
//					to display to the user.

@protocol ReadItLaterDelegate

-(void)readItLaterLoginFinished:(NSString *)stringResponse error:(NSString *)errorString;
-(void)readItLaterSignupFinished:(NSString *)stringResponse error:(NSString *)errorString;
-(void)readItLaterSaveFinished:(NSString *)stringResponse error:(NSString *)errorString;

@end




@interface ReadItLater : NSObject {
	
	id delegate;
	NSString *method;
	NSMutableDictionary *apiResponse;
	NSMutableData *requestData;
	NSString *stringResponse;
	
}
@property (nonatomic, assign) id delegate;
@property (nonatomic, retain) NSString *method;
@property (nonatomic, retain) NSMutableDictionary *apiResponse;
@property (nonatomic, retain) NSMutableData *requestData;
@property (nonatomic, retain) NSString *stringResponse;





// METHODS FOR SAVING A LINK TO READ IT LATER
// for documentation, screenshots, examples, see http://readitlaterlist.com/api_iphone/
// Additional methods are available in the ReadItLaterFull class (see the note at the top of this file for more)


// CUSTOM:		If you'd like to manage displays of loading/result (success/failure)
// --------------------------------------------
// Save a link to Read It Later, RIL will notify the delegate when the request succeeds or fails

// Arguments:
// url - NSURL - link to the page to save
// title - NSString - (optional nil) - title of the page you are saving.  For the best user experience please provide a unique way of identifying the link.  
//									If you have the page loaded in a UIWebView, you can retrieve the title with: 
//									NSString *title = [yourWebView stringByEvaluatingJavaScriptFromString:@"document.title"];
// delegate - id - object to be notified when saving succeeds or fails.  The delegate should implement this selector: - (void)readItLaterFinished:(int)result  --- for result codes, see the delegate documentation
// username - NSString - (optional) - if not provided, this needs to be stored in NSUserDefaults in the key 'ReadItLaterUsername'
// password - NSString - (optional) - if not provided, this needs to be stored in NSUserDefaults in the key 'ReadItLaterPassword'

// Example of use: [ReadItLater save:[NSURL urlWithString:@"http://google.com"] title:@"Google" delegate:self]

+(void)save:(NSURL *)url title:(NSString *)title delegate:(id)delegate;
+(void)save:(NSURL *)url title:(NSString *)title delegate:(id)delegate username:(NSString *)username password:(NSString *)password;



/* ----------------------------------- */

// METHODS FOR HANDLING LOGINS/SIGNUPS
// for documentation, screenshots, examples, see http://readitlaterlist.com/api_iphone/


// --- CUSTOM METHODS:	Use the following methods if you'd like to use your own login or signup screens/forms

// AUTHENTICATION (LOGIN)
// ------------------------
// Test a provided username and password to see if it is correct

// Arguments:
// username - NSString - username (this should be capped at 12 characters - note: I know that is dumb, this limit will be raised in the next few weeks) 
// password - NSString - password (this should be capped at 12 characters - note: I know that is dumb, this limit will be raised in the next few weeks) 
// delegate - id - object to be notified when authentication succeeds or fails.  
//					The delegate should implement this selector:
//					- (void)readItLaterLoginFinished:(NSNumber *)statusCode  --- for result codes, see the delegate documentation

// Example of use: [ReadItLater authWithUsername:@"myUsername" password:@"myPassword" delegate:self]

+(void)authWithUsername:(NSString *)username password:(NSString *)password delegate:(id)delegate;



// SIGNUP 
// ------------------------
// Attempt to register a new account with a username and password

// Arguments:
// username - NSString - username (this should be capped at 12 characters - note: I know that is dumb, this limit will be raised in the next few weeks) 
// password - NSString - password (this should be capped at 12 characters - note: I know that is dumb, this limit will be raised in the next few weeks) 
// delegate - id - object to be notified when authentication succeeds or fails.  
//					The delegate should implement this selector:
//					- (void)readItLaterSignupFinished:(NSNumber *)statusCode  --- for result codes, see the delegate documentation

// Example of use: [ReadItLater signupWithUsername:@"myUsername" password:@"myPassword" delegate:self]

+(void)signupWithUsername:(NSString *)username password:(NSString *)password delegate:(id)delegate;




@end





// -- These are base methods and probably should not be implemented directly -- //

@interface ReadItLater (Private)

-(void)sendRequest:(NSString *)newMethod username:(NSString *)username password:(NSString *)password params:(NSString *)additionalParams;
-(void)finishConnection;
+(NSString *)encode:(NSString *)string;
-(void)done;

@end