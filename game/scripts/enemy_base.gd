extends CharacterBody2D

@export var enemy_stats: EnemyType
@onready var sprite: Sprite2D = $enemy_sprite

var start_position: Vector2
var moving_right: bool

var movement_range = 250

func _ready():
	find_starting_direction()
	_find_appearance()
	start_position = position

func _process(delta):
	move_enemy(delta)
	
	velocity.y += 10
	move_and_slide()

func move_enemy(delta):
	var direction = Vector2.ZERO
	
	if moving_right:
		direction.x += 1
	else:
		direction.x -= 1
		
	position += direction.normalized() * enemy_stats.speed * delta
	
	if position.x >= start_position.x + movement_range:
		moving_right = false
	elif position.x <= start_position.x - movement_range:
		moving_right = true
		
	_update_sprite_direction(direction)

func find_starting_direction():
	var array: Array = [1, 2]
	array.shuffle()
	if array.front() == 1:
		moving_right = true
	else:
		moving_right = false
		
func _update_sprite_direction(dir: Vector2) -> void:
	sprite.flip_h = dir.x < 0
	
func _find_appearance():
	sprite.texture = enemy_stats.texture
	pass
