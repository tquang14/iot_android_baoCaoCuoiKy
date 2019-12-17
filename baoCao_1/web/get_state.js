let r1_state = document.getElementById("relay1");
let r2_state = document.getElementById("relay2");
let r3_state = document.getElementById("relay3");

let temperature = document.getElementById("temperature");
let humidity = document.getElementById("humidity");
let soil_moisture = document.getElementById("soil_moisture");
let light = document.getElementById("light");
let rain = document.getElementById("rain");
let sensor_state = firebase.database().ref('iot_android');
sensor_state.on('value', function(snapshot) {
    console.log(snapshot.val());
    temperature.innerHTML = "Nhiệt độ môi trường: " + snapshot.val()['nhietDo'];
    humidity.innerHTML = "Độ ẩm không khí: " + snapshot.val()['doAmKK'];
    soil_moisture.innerHTML = "Độ ẩm đất: " + snapshot.val()['doAmDat'];
    light.innerHTML = "Cường độ ánh sáng: " + snapshot.val()['anhSang'];
    if (snapshot.val()['mua'] == "false") {
        rain.innerHTML = "Trời hiện ko mưa";
    } else if (snapshot.val()['mua'] == "true") {
        rain.innerHTML = "Trời đang mưa";
    }
});
let relay_state = firebase.database().ref('iot_android_control');
relay_state.on('value', function(snapshot) {
    console.log(snapshot.val());
    r1_state.innerHTML = "bơm " + snapshot.val()['bom'];
    r2_state.innerHTML = "đèn " + snapshot.val()['den'];
    r3_state.innerHTML = "phun sương " + snapshot.val()['phunSuong'];
});