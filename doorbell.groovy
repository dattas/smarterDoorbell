metadata {
	// tile definitions
	tiles {
		standardTile("smarterDoorbell", "device.arduinoThingShield", width: 2, height: 2, canChangeIcon: true, canChangeBackground: true) {
			state "default", label: '${name}'
		}

		main "smarterDoorbell"
		details "smarterDoorbell"
	}
    simulator {
		//I have no idea if this'll work or not
		def str = "ok".collect{new BigInteger(new Integer((byte)it).toString()).toString(16)}.join('')
		status "doorbell":  "catchall: 0104 0000 01 01 0040 00 0A21 00 00 0000 0A 00 0A${str}2E30"
    }
}

Map parse(String description) {
	def result = createEvent(name: "doorbell", value: zigbee.parse(description)?.text)

	log.debug result?.descriptionText
	result
}

def doorbell(){
	zigbee.smartShield(text: "ok").format()
}