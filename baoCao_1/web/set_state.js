const firebaseConfig = {
    apiKey: "AIzaSyDIXsmHu0C9Swyo3dT6dnneJMhw1dMQ5ow",
    authDomain: "testmyled-aa8f7.firebaseapp.com",
    databaseURL: "https://testmyled-aa8f7.firebaseio.com",
    projectId: "testmyled-aa8f7",
    storageBucket: "testmyled-aa8f7.appspot.com",
    messagingSenderId: "378415090064",
    appId: "1:378415090064:web:3c01ac67900f96aea54b15"
};

firebase.initializeApp(firebaseConfig);

function relay1() {
    let relay1 = firebase.database().ref('iot_android_control/bom');
    relay1.once('value', function(snapshot1) {
        if (snapshot1.val() == "on") {
            firebase.database().ref('iot_android_control/bom').set('off');
        } else if (snapshot1.val() == "off") {
            firebase.database().ref('iot_android_control/bom').set('on');
        }
    });
}

function relay1() {
    let relay1 = firebase.database().ref('iot_android_control/bom');
    relay1.once('value', function(snapshot1) {
        if (snapshot1.val() == "on") {
            firebase.database().ref('iot_android_control/bom').set('off');
        } else if (snapshot1.val() == "off") {
            firebase.database().ref('iot_android_control/bom').set('on');
        }
    });
}

function relay2() {
    let relay2 = firebase.database().ref('iot_android_control/den');
    relay2.once('value', function(snapshot1) {
        if (snapshot1.val() == "on") {
            firebase.database().ref('iot_android_control/den').set('off');
        } else if (snapshot1.val() == "off") {
            firebase.database().ref('iot_android_control/den').set('on');
        }
    });
}

function relay3() {
    let relay3 = firebase.database().ref('iot_android_control/phunSuong');
    relay3.once('value', function(snapshot1) {
        if (snapshot1.val() == "on") {
            firebase.database().ref('iot_android_control/phunSuong').set('off');
        } else if (snapshot1.val() == "off") {
            firebase.database().ref('iot_android_control/phunSuong').set('on');
        }
    });
}

// function on() {
//     console.log('on');
//     firebase.database().ref('relay/').set({
//         state: "on"
//     });
// }

// function off() {
//     console.log("off");
//     firebase.database().ref('relay/').set({
//         state: "off"
//     });
// }