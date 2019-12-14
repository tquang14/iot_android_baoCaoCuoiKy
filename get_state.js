let state = document.getElementById("relay_state");
let sensor = document.getElementById("sensor_value");
let relay_state = firebase.database().ref('relay');
relay_state.on('value', function(snapshot) {
    console.log(snapshot.val());
    // let obj = JSON.parse(snapshot.val());
    state.innerHTML = snapshot.val()['state'];
    sensor.innerHTML = snapshot.val()['sensor'];
});

// let sensor_value = firebase.database().ref('relay/sensor');
// sensor_value.on('value', function(snapshot) {
//     console.log(snapshot.val());
//     // let obj = JSON.parse(snapshot.val());
//     sensor.innerHTML = snapshot.val();
// });