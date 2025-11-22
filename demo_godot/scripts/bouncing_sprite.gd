extends Sprite2D

signal direction_changed

@export var speed = 300
var screen_size # Size of the game window.
var velocity = Vector2(speed, speed)
var text_size = texture.get_size()
var bounds = {"top":0, "right":0, "bottom":0, "left":0}

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	screen_size = get_viewport_rect().size
	bounds["right"] = screen_size.x
	bounds["bottom"] = screen_size.y
	
	if position.x > bounds["right"] - text_size.x/2:
		velocity.x = -speed;
		direction_changed.emit(self)
	elif position.x < bounds["left"] + text_size.x/2:
		velocity.x = speed;
		direction_changed.emit(self)

	if position.y < bounds["top"] + text_size.y/2:
		velocity.y = speed;
		direction_changed.emit(self)
	elif position.y > bounds["bottom"] - text_size.y/2:
		velocity.y = -speed;
		direction_changed.emit(self)
		
	position += velocity * delta;


func _on_direction_changed(node: Object) -> void:
	var new_color = Color(randf(),randf(),randf())
	node.self_modulate = new_color
