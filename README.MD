# Map editor for text mode
----------------------------------------------------------------------------

I was going to include a text mode in my Little Game Engine, to implement maps on slow 8088 cpus. So I made this because I wanted a very fast and easy to use map editor for text modes (Playscii is great, but slow and complex to use). 

A good sprite simulation on VGA text modes is not possible, it is slow and very complex when two sprites collide, so I won't be using this for my engine, and also there are other systems in which you can get similar looks (msx, zx spectrum).

This editor uses only 8x8 characters, 16 colours, 2 colours per tile.

Code has bugs, the editor was never finished, and you have to configure a text mode to be 40x25 (320x200) 8x8 cells with no spacing between cells and no blinking (to enable all 16 colours).

<img src="map.png">


# Editor de mapas para modos texto
----------------------------------------------------------------------------

Iba a incluir un modo texto en mi Little Game Engin, para tener mapas y scroll rápido en CPUs muy lentas cono los 8088. Hice este editor para tener un programa simple y rápido, ya que no encontraba lo que quería (por ejemplo Playscii está muy bien, pero es lento y complejo)

Tampoco estaba consiguiendo una simulación de sprites sencilla en el modo texto de VGA, el código es lento y muy complejo, sobre todo cuando dos sprites colisionan. Así que no usaré esto en el motor de juego, y símplemente subiré aqui el editor. Además, hay sistemas como msx y zx spectrum en los que puedes conseguir cosas casi identicas a como se veria un juego en este modo texto de vga.

Éste editor usa caracteres de 8x8, 16 colores y dos colores por celda y tienes que configurar el modo texto como 40x25, celdas de 8x8 sin espacio, y sin parpadeo para activar los 16 colores.

El código tiene bugs y no está completo.

<img src="map.png">
