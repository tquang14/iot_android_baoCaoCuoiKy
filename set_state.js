const firebaseConfig = {
            aapiKey: "AIzaSyADidJtuVL9ZKSgQ-8lF-59oJl8QXrlMzc",
            authDomain: "fill-petrol.firebaseapp.com",
            databaseURL: "https://fill-petrol.firebaseio.com",
            projectId: "fill-petrol",
            storageBucket: "fill-petrol.appspot.com",
            messagingSenderId: "323785293315",
            appId: "1:323785293315:web:7e3daef047c3ca77d19836"
};

firebase.initializeApp(firebaseConfig);

function on() {
    console.log('on');
    firebase.database().ref('relay/').set({
        state: "on"
    });
}

function off() {
    console.log("off");
    firebase.database().ref('relay/').set({
        state: "off"
    });
}

