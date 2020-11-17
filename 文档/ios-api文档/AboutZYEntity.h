//
//  AbouttUser.h
//  ZYIOTSDK
//
//  Created by ZYIT_cxm on 2018/11/27.
//  Copyright © 2018年 cxm. All rights reserved.
//

#import <Foundation/Foundation.h>



/***/
typedef enum {
    /**设备定时任务*/
    ZY_Scene_Type_TimerTask= 0,
    /**设备联动任务*/
    ZY_Scene_Type_DevLinkageTask = 1,
    /**未知*/
    ZY_Scene_Type_None=100
} ZYSceneType;

/**设备套餐类型*/
typedef enum {
    /**历史记录套餐（设备历史记录的存储时长默认7天，套餐内包含设备历史记录不同的存储时长）*/
    ZY_DevCharge_Type_LogRecorder=1,
    /**设备操控套餐（如果设备过期将无法控制设备，套餐内包含延长的设备操控期限）*/
    ZY_DevCharge_Type_Operater= 2
} ZYDevChargeType;


// 定义一个新的类型 是 NSSting * 类型 类型名字叫 PhonePushType
typedef NSString *PhonePushType NS_STRING_ENUM;
/**ios开发时接收推送（因为IOS APP接收推送时开发/发布状态使用的推送证书不一样，所以需要设置）*/
static PhonePushType const PhonePushType_development=@"ios_0";
/**ios已发布，接收推送*/
static PhonePushType const PhonePushType_distribution=@"ios_1";
//回调方法
typedef void(^callbackRetcode)(int retcode,NSString *errDescription);




/**IOT Client与设备进行通信时的消息封装。*/
@interface MyEventData : NSObject
/** 消息ID，可以指定或随机数生成*/
@property(nonatomic) int32_t eventId;
/** 属性名  */
@property(nonatomic, strong) NSString *attrName;
/**属性值类型*/
@property(nonatomic) int32_t attrType;
/**string类型属性值，attrType=1或3时，此值有效*/
@property(nonatomic, strong) NSString *attrValue1;
/**int类型属性值，attrType=2或3时，此值有效*/
@property(nonatomic) int32_t attrValue2;
/**总片数，attrType=4时，此值有效，表示消息被分成几片*/
@property(nonatomic) int32_t totalFrames;
/**当前片位置（1为计数起点），attrType=4时，此值有效，表示本event是消息分隔后的第几片子消息*/
@property(nonatomic) int32_t currentFrame;
/**NSData类型的属性值，attrType=4时，此值有效，表示本片消息内容（若要得到完整消息，需要将分片组合）*/
@property(nonatomic, strong) NSData *attrValue3;
- (instancetype)initWithEventId:(int32_t)eventId attrName:(NSString *)attrName attrType:(int32_t)attrType attrValue1:(NSString *)attrValue1 attrValue2:(int32_t)attrValue2 totalFrames:(int32_t)totalFrames currentFrame:(int32_t)currentFrame attrValue3:(NSData *)attrValue3;
@end

/**用户token类，对应登录时token的解析情况。使用ZYOpenAccount时，userId为空。*/
@interface ZYUserToken : NSObject
/**用户唯一标识，用户注册后生成的*/
@property (nonatomic, strong) NSString *userId;
/**用户登录后的token*/
@property (nonatomic, strong) NSString *token;
/**用户登录后记录状态的令牌标识，本refreshToken未过期时可用本令牌刷新得到新token*/
@property (nonatomic, strong) NSString *refreshToken;
/**用户上次登录的时间(单位：second)*/
@property (nonatomic, strong) NSString *lastLoginTime;
/**用户上次登录的机型*/
@property (nonatomic, strong) NSString *lastLoginPhoneType;
/**用户上次登录的方式：0账号密码登录；1微信授权登录；2Facebook登录*/
@property (nonatomic, strong) NSString *lastLoginWay; 
@end


/**对应获取验证码时的解析情况*/
@interface ZYUserVerifyResult : NSObject
/**请求获取验证码的用户账号*/
@property (nonatomic, strong) NSString *account;
/**验证码发送的方式：false(0)发到手机号码；true(1)发到邮箱*/
@property BOOL isEmailReceiver;
/**如果是发送到手机，则本字段表示剩余的发送短信的次数（防止恶意获取短信验证码）*/
@property  int smsRemain; 
@end


/**筑云 用户信息*/
@interface ZYUser : NSObject
/** 登录后的用户令牌*/
@property (nonatomic, strong) NSString *token;
/** 登录状态保持*/
//@property (nonatomic, strong) NSString *refreshToken;
/**用户唯一标识，用户注册后生成的*/
@property (nonatomic, strong) NSString *userId;
/**用户绑定的手机号码*/
@property (nonatomic, strong) NSString *phoneNum;
/**用户绑定的邮箱 */
@property (nonatomic, strong) NSString *email;
/**用户昵称备注*/
@property (nonatomic, strong) NSString *nickname;
/**用户头像图片名称*/
@property (nonatomic, strong) NSString *headProtrait;
/**用户绑定微信公众号的关系字段，有值则表示已绑定公众号（若想收到微信推送，则需要先调用接口绑定公众号）*/
@property (nonatomic, strong) NSString *wechatPublicOpenid;
/** 用户授权微信登录，本字段有值则表示已授权，可以通过微信授权的账号登录本用户*/
@property (nonatomic, strong) NSString *wechatOauthOpenid;
/**用户授权Facebook登录，本字段有值表示已授权，可以通过Facebook授权的账号登录本用户*/
@property (nonatomic, strong) NSString *facebookOauth;
/**用户的短信发送次数，如找回密码、修改账号功能可能需要发送短信，可以提示用户绑定邮箱，避免短信次数用完影响APP使用。*/
@property int smsRemain;
/**用户登录的手机keyhash，用于标识用户登录的手机，在控制设备时有鉴权。*/
@property (nonatomic, strong) NSString *keyhash;
/**消息中心推送开关，默认true，true表示允许收到来自筑云消息中心的消息推送，false表示不接受推送。*/
@property (nonatomic) BOOL msgSwitch;
/**设备操控记录的总推送开关，默认true，true表示允许收到设备操控记录推送，false表示不接受推送。*/
@property (nonatomic) BOOL pushSwitch;
/**微信-设备操控记录的推送开关，默认true，true表示允许微信收到设备操控记录推送，false表示不接受推送。*/
@property (nonatomic) BOOL wechatSwitch;
/**邮箱-设备操控记录的推送开关，默认true，true表示允许邮箱收到设备操控记录推送，false表示不接受推送。*/
@property (nonatomic) BOOL emailSwitch;
/**手机推送类型，标识APP接收推送的方式：ios_0表示iosApp开发模式，ios_1表示发布模式。（ios app在开发模式与发布模式推送时的证书不一样）*/
@property (nonatomic, strong) NSString *phonePush;
/**推送通道ID，iOS的channelId是devuceToken*/
@property (nonatomic, strong) NSString *channelId;
/**消息免打扰时间段，在这个时间内所有推送消息都关闭。单位：秒(一天中的秒数)，中间用“-”分隔(如12345-86300)，如果结束时间小于起始时间说明是第二天。*/
@property (nonatomic, strong) NSString *noDisturbTime;
/**个性铃声 */
@property (nonatomic, strong) NSString *ring;
/**手机上的语种，可用于决定设备管理员收到的推送内容的语种，目前支持中文、英文。*/
@property (nonatomic, strong) NSString *language;
/**待定保留字段，个人信息*/
@property (nonatomic, strong) NSString *personalInfo;
/**字体大小*/
@property (nonatomic) int16_t fontSize;
/**用户上次登录的时间*/
@property (nonatomic, strong) NSString *lastLoginTime;
/**用户上次登录的机型*/
@property (nonatomic, strong) NSString *lastLoginPhoneType;
/**用户上次登录的方式：0账号密码登录；1微信授权登录；2Facebook登录*/
@property (nonatomic, strong) NSString *lastLoginWay; 
@end



/**对二级用户权限的封装。
 二级用户的权限包含字段说明：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示允许操控的时间区间，如果是时段访问，内容为起始-结束时间戳(单位：秒)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒，中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。shareTime表示分享时间，为时间戳（单位秒）。
形如：{"type":"2","time":"12345-23456","week":"146","shareTime":"1567898770"}
*
* type=0全时； 1（时间戳内）；2（每周重复）
*
*/
@interface AuthorityEntity : NSObject
/**0表示全时访问，无需time和week；
 * 1表示时段访问，无需week，需要设置time（时间戳单位是秒）；
 * 2表示定期访问，需要设置week、time
 *
 */
@property int validType;
/**二级用户权限被创建的时间，单位：秒
 * create this valid time=share timestamp
 */
@property long long shareTime;

/**根据json内容新建一个权限封装*/
+(AuthorityEntity *) initAuthorityWithJsonStr:(NSString *)jsonStr;
/**根据权限类型新建一个权限封装（type=0时使用）*/
+(AuthorityEntity *) initAuthorityWithValidType:(int )validType;
/**获取当前权限的json描述*/
-(NSString *) getJsonStrAuthorityDescription;
@end

/** 二级用户权限——时段访问（年月日日期时间段）type=1 */
@interface  AuthorityEntity1:AuthorityEntity
/**timestamp1-timestamp2分别是是年月日时间戳区间起点和终点，不可相同
 */
@property long long timestamp1;
@property long long timestamp2;
@end

/**二级用户权限——定期访问（周重复模式） type=2*/
@interface  AuthorityEntity2:AuthorityEntity
/**time1-time2是时间点区间，可重复（每天时间有24小时）
 */
@property int time1;
@property int time2;
/**week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日*/
@property (nonatomic, strong) NSString *weekMode;
@end

/**临时用户权限*/
@interface  AuthorityTempEntity:NSObject
/*
 *0表示时段控制，1表示时段单次控制（控制后即失效）
 */
@property int validType;

/**临时用户权限被创建的时间，单位：秒
 */
@property long long shareTime;

/**临时用户权限被使用的时间（临时用户控制设备），单位：秒
 */
@property long long controlTime;

/**timestamp1-timestamp2分别是年月日时间戳区间起点和终点，不可相同。
 (时间戳单位：second)
 */
@property long long timestamp1;
@property long long timestamp2;

/**根据json内容新建一个权限封装*/
+(AuthorityTempEntity *) initAuthorityWithJsonStr:(NSString *)jsonStr;
/**新建一个权限封装 */
+(AuthorityTempEntity *) initAuthorityWithValidType:(int)validType timestamp1:(long long)timestamp1 timestamp2:(long long) timestamp2;
/**获取当前权限的json描述*/
-(NSString *) getJsonStrAuthorityDescription;
@end

@interface ZYAuthUser :NSObject
/**用户唯一标识，用户注册后生成的*/
@property (nonatomic, strong) NSString *authUserId;
/** 权限级别，1是一级用户-管理员操控设备无时间限制，2是二级用户操控设备的时间权限由管理员设定*/
@property (nonatomic)  int level;
/**权限包含字段说明：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示操控时间，如果是时段访问，内容为起始-结束时间戳(单位：second)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8点对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。shareTime表示分享时间，为时间戳。
 形如：{"type":"2","time":"12345-53346","week":"146","shareTime":"1567898770"}*/
@property (nonatomic, strong) AuthorityEntity *authority;
/**用户绑定的手机号码*/
@property (nonatomic, strong) NSString *phoneNum;
/**用户绑定的邮箱 */
@property (nonatomic, strong) NSString *email;
/**用户昵称备注*/
@property (nonatomic, strong) NSString *nickname;
/**用户头像图片名称*/
@property (nonatomic, strong) NSString *headProtrait;
/**管理员为二级用户备注*/
@property (nonatomic, strong) NSString *remark;
@end

@interface ZYTempUser :NSObject
/**用户唯一标识，用户注册后生成的*/
@property (nonatomic, strong) NSString *tempShareId;
/**权限说明，包含两种访问权限，一种是时段控制，一种是时段单次控制（控制后即失效），(时间戳单位：second)。
    时段控制格式如下：{"type": "0","time": "1434500000-1435600000","shareTime": "1534500000"}；时段单次控制格式如下：{"type": "1","time": "1434500000-1435600000","controlTime": "1435500000","shareTime": "1434500000"}。
    type为0表示时段控制，为1表示时段单次控制。
    time包含起始和结束时间戳，中间用-隔开，精确到秒。
    controlTime为操控时间，只针对时段单次控制有效，如果control_time为空，表示未操控，为时间戳表示操控时间。
    shareTime为临时用户分享时间。
    所有字段都为String格式。*/
@property (nonatomic, strong) AuthorityTempEntity *authority;
/**管理员为临时用户备注*/
@property (nonatomic, strong) NSString *remark;
@end


/**设备属性类封装，全局属性与普通属性的区别是全局属性值由厂家设置，不允许用户修改，且没有时间戳值*/
@interface DeviceAttrEntity : NSObject
/**属性名*/
@property (strong, nonatomic) NSString *name;
/**属性值*/
@property (strong, nonatomic) NSString *value;
/**属性值修改时间，(时间戳单位：ms，毫秒)*/
@property  long long timestamp;
@end


/**设备绑定的摄像头信息封装如下：（如萤石摄像头）*/
@interface DeviceCameraInfo : NSObject
/**摄像头ID，摄像头设备标识*/
@property (strong,nonatomic) NSString *cameraId;

/**摄像头视频数据的原密码，设备说明书上标注的摄像头默认验证码（密码）。如果摄像头的拥有者没有修改摄像头的密码，则此密码有效，视频被加密可用此密码解密获取到的视频数据 */
@property (strong,nonatomic) NSString *originalPassword;

/**摄像头视频数据的密码，如果摄像头的拥有者修改了摄像头的密码，则原密码无效，应使用本密码解密获取的被加密视频数据 */
@property (strong,nonatomic) NSString *password;

/**摄像头型号（预留，暂不支持）*/
@property (strong,nonatomic) NSString *type;

/**萤石用户的accessToken，绑定摄像头时请先调用萤石相关接口检查当前萤石SDK内在登用户是否拥有这个摄像头。
 * APP使用萤石SDK需要先设置这个值才可以操作摄像头，如查看摄像头。
 * 后台保存accessToken值是为了共享摄像头，不需要在不同的手机萤石重复授权登录筑云*/
@property (strong,nonatomic) NSString *accessToken;
/**以json格式获取摄像头信息*/
-(NSString *)getJsonStrDescription;
@end


/**设备，对应一个属性字典<NSString(attrName):DeviceAttrEntity(attr)>*/
@interface DeviceInfoEntity : NSObject{
    /**属性字典：attrName:deviceAttr*/
    NSMutableDictionary *_attrDics;
}
/**设备唯一ID，可在设备二维码上找到*/
@property (strong, nonatomic) NSString *keyhash;
/**设备权限，1是管理员，操控设备无时间限制；2是二级用户，操控设备的时间权限由管理员设定*/
@property ( nonatomic) int level;
/**设备类型ID，可在设备二维码上找到*/
@property int devTypeId;
/**用户的推送开关，默认开(true)，暂不支持设置*/
@property (nonatomic) BOOL pushSwitch;
/**用户的邮箱推送开关，默认开(true)，暂不支持设置*/
@property (nonatomic) BOOL emailSwitch;
/**用户的微信推送开关，默认开(true)，暂不支持设置*/
@property (nonatomic) BOOL wechatSwitch;
/**用户控制权限，json格式数据，(时间戳单位：second)：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示操控时间，如果是时段访问，内容为起始-结束时间戳，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8点对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。shareTime表示分享时间戳。
 形如：{"type":"2","time":"1564500000-1595600000","week":"146","shareTime":"1567898770"}*/
@property (strong, nonatomic) AuthorityEntity *authority;
 /**get属性字典：<attrName:deviceAttr>*/
-(NSMutableDictionary *) attrDics;
 /**set属性字典：<attrName:deviceAttr>*/
-(void) attrDics:(NSMutableDictionary *)attrs;

/**为设备增加一个属性值（name,value,timestamp）(属性值对应的时间戳单位：ms，毫秒)
 */
-(void) addAttr:(NSString *)name :(NSString *)value :(NSString *)timestamp;

/**获取指定名称的属性实体:DeviceAttrEntity
 */
-(DeviceAttrEntity *) getAttrOne:(NSString *) name;
/**获取设备状态是否在线*/
-(BOOL)getOnline;
/**获取设备过期时间，一旦设备过期将无法控制设备，除非购买设备操控套餐以延长操控期限*/
-(long long)getDevExpireTime;
/**
 获取设备名称：统一在没有名称的时候使用keyhash
 */
-(NSString *) getAttrDevNameValue ;

 /**封装设备名称属性*/
-(void)setAttrDevNameValue:(NSString *)devName;

/**获取设备绑定的摄像头信息，返回为空时表示没有绑定摄像头；否则表示有绑定摄像头.
 * 有绑定摄像头时返回的内容：cameraId，pwd，originalPwd，accessToken*/
-(DeviceCameraInfo *)getDevCameraInfo;

@end


/**设备历史记录封装，历史记录的类型:1指设备异常-如设备上下线；2指操控记录；3指分享与绑定；4指其它。
 **/
@interface DeviceLogEntity:NSObject
/**设备keyhash*/
@property (strong,nonatomic) NSString *keyhash;
/**属性名*/
@property (strong,nonatomic) NSString *attrName;
/**属性值*/
@property (strong,nonatomic) NSString *attrValue;
/**属性值解析后的文字内容（与APP/微信/邮箱接收到的推送内容一样）*/
@property (strong,nonatomic) NSString *content;
/**历史记录的类型，1异常-如设备上下线；2操控；3分享；4其它*/
@property (strong,nonatomic) NSString *type;
/**历史记录产生的时间戳(时间戳单位：second)*/
@property (strong,nonatomic) NSString *timestamp;
/**如果绑定摄像头，且有抓拍到图片，则本字段表示抓拍的图片路径*/
@property (strong,nonatomic) NSString *capture;
@end

/**设备场景封装 */
@interface DeviceSceneInfo :NSObject
 /**场景标识ID，创建场景后可得*/
@property (strong,nonatomic)  NSString *sceneId;
/**场景类型：0定时；1联动 */
@property ( nonatomic)  int   typeId;
/**场景名称，由用户设定*/
@property (strong,nonatomic)  NSString  *name;
/**场景创建时间(时间戳单位：second)*/
@property ( nonatomic) long long timestamp;
/**场景备注信息，预留*/
@property (strong,nonatomic)  NSString  *remark ;
/**场景内的任务列表，定时任务列表或联动任务列表*/
@property (strong,nonatomic) NSMutableArray *tasks;
@end


/**定时任务时间有两种，一种是定期单次任务，一种是周重复任务。定期单次任务是指定具体时间，为年月日时分的时间戳，周重复任务是指定周几的几时几分。最小精确到分钟。设备管理员才可以为设备设置定时。
 (时间戳单位：second)*/
@interface DeviceTimedTask :NSObject
/**定时任务标识ID，创建定时任务后可得*/
@property (strong,nonatomic)  NSString *timedTaskId;
/**任务触发时间，如果是定期单次，如北京时间2017/11/7 10:26:00，存储为1510021560(时间戳单位：second)。如果是周重复任务，time为小时分钟转换成秒数，小时分钟随系统时间。*/
@property  long long time;
/**任务重复，如果是定期单次任务，repeat为空。如果是周重复任务（分隔符是英文分号），repeat才有效。repeat值为1,2,3,4,5,6,7，分别代表周一到周日，此处多天时必须用英文逗号隔开。如值为"1,3,6"表示"周一 周三 周六"。*/
@property (strong,nonatomic) NSString *repeat;
/**指定执行的设备*/
@property (strong,nonatomic) NSString *keyhash;
/**属性名，指定执行的动作名*/
@property (strong,nonatomic) NSString *attrName;
/**属性值，指定执行的动作*/
@property (strong,nonatomic) NSString *attrValue;
/**备注*/
@property (strong,nonatomic) NSString *remark;
/**场景标识ID，创建场景后可得。若本定时任务没有添加到场景中，则本字段为空*/
@property (strong,nonatomic)  NSString *sceneId;
@end



/**对设备联动时间限制的封装。
 字段说明：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示联动时间，如果是时段访问，内容为起始-结束年月日对应时间戳(单位：second)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8:00对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。
    形如：{"type":"2","time":"12345-23456","week":"127"}
 * type=0全时； 1（时间戳内）；2（每周重复）
 *
 */
@interface AuthorityEntityDevTimeLimit : NSObject
/**0表示全时访问，无需time和week；
 * 1表示时段访问，无需week，需要设置time（时间戳单位是秒）；
 * 2表示定期访问，需要设置week、time
 *
 */
@property int validType;

/**根据json内容新建一个时间限制权限封装*/
+(AuthorityEntityDevTimeLimit *) initAuthorityWithJsonStr:(NSString *)jsonStr;
/**根据权限类型新建一个时间限制权限封装（type=0时使用）*/
+(AuthorityEntityDevTimeLimit *) initAuthorityWithValidType:(int )validType;
/**获取当前时间限制权限的json描述*/
-(NSString *) getJsonStrAuthorityDescription;
@end

/** 设备联动时间限制——时段访问（年月日日期时间段）type=1 */
@interface  AuthorityEntityDevTimeLimit1:AuthorityEntityDevTimeLimit
/**timestamp1-timestamp2分别是是年月日时间戳区间起点和终点，不可相同
 */
@property long long timestamp1;
@property long long timestamp2;
@end

/** 设备联动时间限制——定期访问（周重复模式） type=2*/
@interface  AuthorityEntityDevTimeLimit2:AuthorityEntityDevTimeLimit
/**time1-time2是时间点区间，可重复（每天时间有24小时）
 */
@property int time1;
@property int time2;
/**week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日*/
@property (nonatomic, strong) NSString *weekMode;
@end


/**设备联动，可以是同一个设备联动，也可以是同一个用户下的不同设备联动。若设备操控时间过期，设备联动将不能成功。设备联动执行时没有返回结果，如果有设置推送，则有推送通知。*/
@interface DeviceLinkage :NSObject
/**联动任务标识ID，创建联动任务后可得*/
@property (strong,nonatomic)  NSString *linkageId;
/**时间限制，json格式数据：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示联动时间，如果是时段访问，内容为起始-结束年月日对应时间戳(单位：second)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8:00对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。
 形如：{"type":"2","time":"12345-23456","week":"127"}*/
@property (strong,nonatomic) AuthorityEntityDevTimeLimit *timelimit;
/**指定触发的设备*/
@property (strong,nonatomic) NSString *keyhash;
/**属性名，指定触发的动作名*/
@property (strong,nonatomic) NSString *attrName;
/** 触发条件——属性值条件判断。json格式数据，包含operation，threshold。operation：触发条件，包括：>，<，>=，<=，==，!=，contains，equals。threshold：阈值。
 形如：{"operation":">","threshold":"20"} */
@property (strong,nonatomic) NSString *condition;
/**触发后执行的设备*/
@property (strong,nonatomic) NSString *keyhash2;
/**属性名，触发后执行的动作名*/
@property (strong,nonatomic) NSString *attrName2;
/**属性值，触发后执行的动作*/
@property (strong,nonatomic) NSString *attrValue2;
/**备注*/
@property (strong,nonatomic) NSString *remark;
/**场景标识ID，创建场景后可得。若本定时任务没有添加到场景中，则本字段为空*/
@property (strong,nonatomic)  NSString *sceneId;
@end


/**属性定义，包括属性不同取值时的文字含义——含中英文*/
@interface DevAttrOperation :NSObject
/**属性定义ID*/
@property (strong,nonatomic) NSString *operId ;
/**操作内容，属性作为触发条件时的属性定义，json数据。根据不同的属性值类型，有不同的定义，
 如int时：{"intC": {"defaultV": 20,"max": 10,"min": 40,
    "==": {"en": "temperature equal(℃)","zh": "温度等于（度）"},
    "<": {"en": "temperature lower(℃)","zh": "温度小于（度）"},
    ">": {"en": "temperature Upper(℃)","zh": "温度大于（度）"}
    }}
 具体定义详见属性定义JSON说明文档。*/
@property (strong,nonatomic) NSString *operation  ;
/**属性名*/
@property (strong,nonatomic) NSString *attrName ;
/**定时执行或被联动任务导致执行时的属性值定义，json数据。根据不同的属性值类型，有不同的定义，如int时：{
 "intVas": { "defaultV": 50,"lang": {"en": "temperature(℃)","zh": "温度(度)"},"max": 80,"min":10}}
 具体定义详见属性定义JSON说明文档。*/
@property (strong,nonatomic) NSString *attrValue  ;
@end



/**设备触发器，当本类型的设备的属性值变化时，按照如下配置后台执行。*/
@interface DevTrigger :NSObject
/**触发器标识*/
@property (strong,nonatomic) NSString *triggerId;
/**设备类型ID*/
@property (strong,nonatomic) NSString *devTypeId ;
/**属性名*/
@property (strong,nonatomic) NSString *attrName ;
/**当被触发时，是否推送，默认false不推送*/
@property (nonatomic) BOOL isPush ;
/**当被触发的行为发生时，是否将行为存储为log历史记录，默认false不存储*/
@property (nonatomic) BOOL isSave ;
/**历史记录存储时间，单位：天，默认7天，如果购买套餐则以套餐时间为准*/
@property (strong,nonatomic) NSString *saveTime ;
/**是否抓拍，默认false不抓拍。（需要触发器的isSave=true且设备已绑定摄像头时才有效，将调用设备属性的camera中摄像头token抓拍图片。）*/
@property (nonatomic) BOOL isCapture ;
/**相关用户类型，指的是可查看被触发后产生的历史记录的用户群
 0仅管理员；1管理员与二级用户；2所有用户，默认为1。*/
@property (strong,nonatomic) NSString *relatedUserType ;
/**触发器类型，0默认，达到条件就触发；1阈值恢复，第一次满足条件时触发，下一次由false变为true时触发——满足触发条件时为true，否则为false；2自动失效，触发一次后自动失效，只有再打开后才生效(用户可以设置开启或关闭)。
 如阈值恢复：检测设备电池电量，当用户设备自定义触发器时设定设备低于20%时触发——只在第一次低于20%时触发，如果后续一直低于20%，不再触发。只有充电后电量高于20%后，再低于20%才会触发。*/
@property (strong,nonatomic) NSString *type ;
@end



/**设备自定义触发器，是设备触发器的拓展——设备触发器针对设备类型下的所有设备，设备自定义触发器针对指定设备。
 不同用户可以根据自身需求设定不同的属性值，进行推送。比如，婴儿体温计A用户设置>37度才触发；B用户设置>38度触发；C用户未设置。那么C用户的温度计只要温度变化都将收到推送通知(此时未自定义，则使用设备触发器默认配置)，A用户在大于37时会收到通知，B用户在大于38时会收到通知*/
@interface DevCustomerTrigger :NSObject
/**触发器标识*/
@property (strong,nonatomic) NSString *triggerId;
/**设备类型ID*/
//@property (strong,nonatomic) NSString *devTypeId ;
/**设备标识*/
@property (strong,nonatomic) NSString *keyhash ;
/**属性名*/
@property (strong,nonatomic) NSString *attrName ;
/**触发状态，是否可触发，默认true可触发*/
@property (nonatomic) BOOL status ;
/**时间限制，字段说明：type：操控类型，0表示全时访问，无需time和week；1表示时段访问，无需week；2表示定期访问。time表示操控时间，如果是时段访问，内容为起始-结束时间戳(单位：second)，中间用-分割；如果是定期访问，内容为当天时间的起始秒-结束秒（24小时制 ，如上午8点对应的秒数是28800），中间用-分割。week表示星期，1-7分别表示周一到周日，如：137表示周一周三周日。
 形如：{"type":"2","time":"12345-23456","week":"127"}*/
@property (strong,nonatomic) AuthorityEntityDevTimeLimit *timelimit;
/** 触发条件——属性值条件判断。json格式数据，包含operation，threshold。operation：触发条件，包括：>，<，>=，<=，==，!=，contains，equals。threshold：阈值。
 形如：{"operation":">","threshold":"20"} */
@property (strong,nonatomic) NSString *condition;
/**备注*/
@property (strong,nonatomic) NSString *remark ;
@end


/**设备套餐。可购买设备历史记录存储时间、可购买延长设备的操控期限。**/
@interface ChargeInfoDev : NSObject
/** 设备套餐id，*/
@property (strong,nonatomic) NSString *chargeId;

/** 设备类型Id */
@property int  devTypeId;

/**套餐类型标志， 1：历史记录套餐  2：操控套餐*/
@property ZYDevChargeType mark;

/**套餐价格，单位：分*/
@property int price;

/**循环存储时间，单位天。 （仅指历史记录的存储时间，与设备操控套餐无关）*/
@property int saveTime;

/**套餐有效期限，单位天。
 * （设备操控套餐中本字段表示设备操控期限延长的天数，历史记录套餐中本字段表示购买后套餐有效期间指定activeTime天数内本套餐内的历史记录saveTime值有效）*/
@property int activeTime;

/**套餐折扣信息，显示给用户看*/
@property (strong,nonatomic) NSString *discountInfo;
/**设置套餐类型*/
-(void)setMarkForInt:(int)chargeMark;
@end


/** 已购买设备套餐信息**/
@interface ChargeDevPurchase : NSObject
/**套餐类型标志， 1：历史记录套餐  2：操控套餐*/
@property ZYDevChargeType chargeMark;
/** 摄像头账号*/
@property (strong,nonatomic) NSString *keyhash;
/**购买套餐的过期时间*/
@property long long expireTime;
/**购买套餐详情，包含每一次购买的信息，json格式，如：”[ {"time":"1234567890-1345678999","charge_id":”s”},{"time":"132011000-1401810110","charge_id":"s2"}]”,time的单位是秒*/
@property (strong,nonatomic) NSString *details;
/**月推邮箱，允许额外绑定两个（用英文符号分号“;”分隔开，如“cxm@zy.com;c2@yun.com”），默认包含设备管理员邮箱（管理员邮箱一定推送）*/
@property (strong,nonatomic) NSString *email;
/**设置套餐类型*/
-(void)setChargeMarkForInt:(int)chargeMark;
@end


/**短信套餐。用户获取短信验证码次数有限（默认10次），购买短信套餐可以增加获取短信验证码次数**/
@interface ChargeInfoSMS : NSObject
/**套餐id*/
@property (strong,nonatomic) NSString *chargeId;
/**套餐价格，单位：分。*/
@property int price;
/**短信数(获取验证码次数)*/
@property int smsCount;
/**折扣信息，显示给用户看*/
@property (strong,nonatomic) NSString *discount;
@end

/**服务器的DNS信息,包含TenantId、ZOT模块IP和域名地址、IOT(XOT)地址、服务器名称等**/
@interface ServerDNSInfoEntity : NSObject
    /**标识这个服务器DNS信息*/
    @property int Id;
    /**APP支持的TennatId*/
    @property int tenantId;
    /**ZOT所在服务器的域名*/
    @property (strong,nonatomic) NSString *zotDomain;
    /**ZOT所在服务器的IP*/
    @property (strong,nonatomic) NSString *zotIp;
    /**XOT（IOT）程序所在服务器的域名或IP列表，形如“地址;地址;地址”*/
    @property (strong,nonatomic) NSString *xot;
    /**服务器名称 ：键是语言，值是对应语言的服务器名称，如en:china,zh:中国大陆*/
    @property (strong,nonatomic) NSDictionary *serverNames;
    /***
     * 根据APP语言获取服务器名称
     * @param language  APP语言
     * @return serverName
     */
    -(NSString*)getServerNameWithLanguage:(NSString *)language;
@end

/** APP版本下的服务器DNS信息列表 **/
@interface HttpDNSInfoEntity : NSObject
/**APP版本（APP可以根据自己的版本选择可使用的服务器）*/
@property (strong,nonatomic) NSString *version;

/**单位：秒，HttpDNS信息的有效时间。建议获取DNS信息过了指定秒数时间后重新获取新的DNS信息*/
@property long refreshTime  ;

/**List<ServerDNSInfo>,DNS信息，包含支持的服务器地址信息及其Tenant账号*/
@property (strong,nonatomic) NSMutableArray *servers;
@end




/**筑云消息中心的消息*/
@interface  MessageInfoEntity : NSObject
/**发布时间，按时间戳降序排序*/
@property  long long newstime;

/**起始时间*/
@property  long long startTime;

/**过期时间*/
@property  long long expireTime;

/**消息标题*/
@property (strong,nonatomic) NSString *title;

/**消息内容*/
@property (strong,nonatomic) NSString *content;

/** 针对的设备类型Id，如果有多个设备类型，用英文符号分号“;”隔开，如“1;21”表示本消息与设备类型1和21有关。如果为0，说明针对所有设备类型。*/
@property (strong,nonatomic) NSString *devTypeId;

/**消息类型Id*/
@property  int msgTypeId;
@end


/** 筑云消息中心被删除的消息（有的消息被消息中心删除了需要APP也删除本地缓存）*/
@interface DeleteMessageInfoEntity : NSObject
/**发布时间，按时间戳降序排序*/
@property  long long newstime;

/**消息类型id*/
@property  int msgTypeId;

/**是否应该删除本地数据库记录,1表示要删除*/
@property  int isDelete;

@end


/**筑云消息中心的消息类型*/
@interface MessageTypeEntity : NSObject
/**消息类型Id*/
@property int msgTypeId;

/**消息类型名称*/
@property (strong,nonatomic) NSString *name;
@end
