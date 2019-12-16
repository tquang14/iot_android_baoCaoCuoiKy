function add_data() {
    // addData(ten_chart, data.labels)
    console.log(parseInt(ten_chart.data.labels.slice(-1)[0], 10) + 1);
    let label = parseInt(ten_chart.data.labels.slice(-1)[0], 10) + 1;
    //console.log(ten_chart.data.labels);
    addData(ten_chart, label.toString(), 95072);
}

function addData(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
}