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

let temperature = firebase.database().ref('iot_android/nhietDo');

function get_data_every_30s() {
    temperature.once('value', function(snapshot) {
        console.log(snapshot.val());
        let data = parseInt(snapshot.val());
        console.log(typeof data);
        add_data(data);
    });
    setTimeout(get_data_every_30s, 10000);
}

get_data_every_30s();
let sensor = firebase.database().ref('iot_android');
sensor.on('value', function(snapshot) {
    console.log(snapshot.val());
    //let data = parseInt(snapshot.val());
    //console.log(typeof data);
    //add_data(data);
});

function on() {
    firebase.database().ref('iot_android/nhietDo').set(30);
}