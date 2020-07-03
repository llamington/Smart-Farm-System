

get_sensor_data = (column, period) => {
    return $.ajax({
        url: '/api/sensor_data',
        dataType: 'json',
        type: 'GET',
        data: {
            column: column,
            period: period
        }
    })
}
temp_promise = get_sensor_data('air_temperature', 7)
temp_promise.done((data) => {insert_chart('#chart1', data)});

insert_chart = (chart_div, json_data) => {
    new Chart($(chart_div)[0].getContext('2d'), {
        // The type of chart we want to create
        type: 'line',

        // The data for our dataset
        data: {
            labels: json_data['date_time_list'],
            datasets: [{
                label: 'My First dataset',
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: json_data['data_list']
            }]
        },

        // Configuration options go here
        options: {}
    });

}