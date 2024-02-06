extends Area2D
signal hit

@export var speed = 100 # pixels/sec
var screen_size

# Called when the node enters the scene tree for the first time.
func _ready():
	#var animation_prio = 0
	$AnimatedSprite2D.play("default",0)
	screen_size = get_viewport_rect().size
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var velocity = Vector2.ZERO # player's movement vector.
	var speed_multiplier = 1
	var isAttacking = false
	if Input.is_action_pressed("attack"):
		$AnimatedSprite2D.play("attack")
	if $AnimatedSprite2D.get_animation() == "attack":
		isAttacking = true
		if $AnimatedSprite2D.get_frame() == 4:
			velocity.x += 7000 #TODO find a better way to do this
			#velocity = velocity.normalized() * speed * speed_multiplier
			position += velocity * delta
			position = position.clamp(Vector2.ZERO, screen_size)
			
	else:
		isAttacking = false
	
	if not isAttacking:	#o_O
		if Input.is_action_pressed("move_right"):
			velocity.x += 1
		if Input.is_action_pressed("move_left"):
			velocity.x -= 1
		if Input.is_action_pressed("move_down"):
			velocity.y += 1
		if Input.is_action_pressed("move_up"):
			velocity.y -= 1

		if Input.is_action_pressed("shift"):
			speed_multiplier = 10
		
		if velocity.length() > 0:
			velocity = velocity.normalized() * speed * speed_multiplier
			#if not isAttacking:
			$AnimatedSprite2D.play("default")
		else:
			if $AnimatedSprite2D.get_animation() == "default":
				$AnimatedSprite2D.stop()

		position += velocity * delta
		position = position.clamp(Vector2.ZERO, screen_size)


func _on_body_entered(body):
	hide() # Player disappears after being hit.
	hit.emit()
	# Must be deferred as we can't change physics properties on a physics callback.
	$CollisionShape2D.set_deferred("disabled", true)

func start(pos):
	position = pos
	show()
	$CollisionShape2D.disabled = false


func _on_animated_sprite_2d_animation_finished():
	if $AnimatedSprite2D.get_animation() == "attack":
		$AnimatedSprite2D.play("default",0)
