function doPost(e) { // doPost se ejecuta cuando un programa envía una solicitud HTTP POST a una app web (Aplicación de Google Sheets en este caso)
  var sheet =
  SpreadsheetApp.getActiveSpreadsheet().getActiveSheet(); // Se muestra la hoja de cálculo activa actualmente y luego se obtiene esa hoja que está activa
  var data = JSON.parse(e.postData.contents); // Con parse() se convierten los datos de la solicitud en un objeto de JavaScript, primero se obtiene el texto del contenido en la solicitud POST con e.postData.contents
  sheet.appendRow([new Date(), data.tempC, data.tempF]); // Agrega una nueva fila a la hoja de cálculo con los datos enviados en la solicitud y la fecha actual
}