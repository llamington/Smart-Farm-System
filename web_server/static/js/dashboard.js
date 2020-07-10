get_sensor_data = (sensor_type, sensor_id, period=null) => {
    return $.ajax({
        url: '/api/sensor_data',
        dataType: 'json',
        type: 'GET',
        data: {
            period: period,
            sensor_type: sensor_type,
            sensor_id: sensor_id
        }
    })
}
let soil_humidity_gauge;
let soil_leaching_gauge;

get_sensor_data('soil_humidity', 1, 7).done((data) => {insert_line_chart('#soil_humidity_graph', data, 'soil_humidity')})
get_sensor_data('soil_temperature', 1, 7).done((data) => {insert_line_chart('#soil_temperature_graph', data, 'soil_temperature')})
get_sensor_data('ph', 1, 7).done((data) => {insert_line_chart('#soil_ph_graph', data, 'Soil pH')})
get_sensor_data('soil_humidity', 1).done((data) => {soil_humidity_gauge = insert_gauge_chart('soil_humidity_gauge', data, soil_moisture_sectors)})

//placeholder leaching likelihood gauge
insert_gauge_chart('soil_leaching_gauge', 45, soil_leaching_sectors)

let sensor_map = new SensorMap('sensor_map')

let sensors_geojson_promise = $.ajax({
    url: '/api/sensors_geojson',
    dataType: 'json',
    type: 'GET'
})
sensors_geojson_promise.done((data) => {
    sensor_map.insert_geojson(data, on_click_function)
})

on_click_function = (event) => {
    let sensor_id = event.target.feature.properties.id
    get_sensor_data('soil_humidity', sensor_id, 7).done((data) => {insert_line_chart('#soil_humidity_graph', data, 'soil_humidity')})
    get_sensor_data('soil_temperature', sensor_id, 7).done((data) => {insert_line_chart('#soil_temperature_graph', data, 'soil_temperature')})
    get_sensor_data('ph', sensor_id, 7).done((data) => {insert_line_chart('#soil_ph_graph', data, 'Soil pH')})
    get_sensor_data('soil_humidity', sensor_id).done((data) => {soil_humidity_gauge.refresh(data)})
}