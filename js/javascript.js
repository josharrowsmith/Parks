
function initMap() {
	// set the map
	var myLatLng = {lat: -27.467401, lng: 153.025101};

	// Initialise map
	map = new google.maps.Map(document.getElementById('googleMap'), {
	  zoom: 10,
	  center: myLatLng,
	  mapTypeId: google.maps.MapTypeId.ROADMAP,
		 streetViewControl: true,
		draggable: false,
					 zoomControl: false,
					 scrollwheel: false

	});

	// Add bounds to map
	bounds = new google.maps.LatLngBounds();
}

function addMarkerToMap(latitude,longitude,labelString,url,rating,suburb,street){
	// Create a location array
	var myLatLng = {lat: parseFloat(latitude), lng: parseFloat(longitude)};

	// Create label for the marker
	var contentString = "<h3><a href='"+url+"'>"+labelString+"</a></h3>"+
						"<b>Suburb: </>"+suburb+"<br/>"+
						"<b>Street: </>"+street+"<br/>"+
						"<b>Rating: </>"+rating+"<br/>";

	// Use label to create an info window in marker
	var infowindow = new google.maps.InfoWindow({
		content: contentString
	});

	// Create the marker
	var marker = new google.maps.Marker({
		position: myLatLng,
		map: map,
		title: contentString,
		url: url
	});

	// add a listener to open the info window when clicked
	marker.addListener('click', function() {
		infowindow.open(map, marker);
	});

	// Extend the bound of the map to include marker
	loc = new google.maps.LatLng(marker.position.lat(), marker.position.lng());
	bounds.extend(loc);

	// Fit and center the map to the bounds
	map.fitBounds(bounds);
	map.panToBounds(bounds);
}
