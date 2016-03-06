 #   g a m e o f l i f e 
 
 - -   A b o u t   g a m e   o f   l i f e   - - 
 / *   W i k i p e d i a 
 T h e   G a m e   o f   L i f e ,   a l s o   k n o w n   s i m p l y   a s   L i f e ,   i s   a   c e l l u l a r   a u t o m a t o n   d e v i s e d   b y 
 t h e   B r i t i s h   m a t h e m a t i c i a n   J o h n   H o r t o n   C o n w a y   i n   1 9 7 0 . [ 1 ] 
 
 T h e   " g a m e "   i s   a   z e r o - p l a y e r   g a m e ,   m e a n i n g   t h a t   i t s   e v o l u t i o n   i s   d e t e r m i n e d   b y 
 i t s   i n i t i a l   s t a t e ,   r e q u i r i n g   n o   f u r t h e r   i n p u t .   O n e   i n t e r a c t s   w i t h   t h e 
 G a m e   o f   L i f e   b y   c r e a t i n g   a n   i n i t i a l   c o n f i g u r a t i o n   a n d   o b s e r v i n g   h o w   i t   e v o l v e s 
 o r ,   f o r   a d v a n c e d   p l a y e r s ,   b y   c r e a t i n g   p a t t e r n s   w i t h   p a r t i c u l a r   p r o p e r t i e s . 
 W i k i p e d i a   * / 
 
 - -   A b o u t   t h i s   i m p l e m e n t a t i o n   - - 
 T h i s   i s   m y   i m p l e m e n t a t i o n   o f   g a m e   o f   l i f e   f o r   L i n u x ,   w r i t t e n   i n   C   a n d   r e l e a s e d 
 u n d e r   M I T - l i c e n s e . 
 
 - -   R u l e s   - - 
 / *   W i k i p e d i a 
 T h e   u n i v e r s e   o f   t h e   G a m e   o f   L i f e   i s   a n   i n f i n i t e   t w o - d i m e n s i o n a l   o r t h o g o n a l   g r i d 
 o f   s q u a r e   c e l l s ,   e a c h   o f   w h i c h   i s   i n   o n e   o f   t w o   p o s s i b l e   s t a t e s ,   a l i v e   o r   d e a d . 
 E v e r y   c e l l   i n t e r a c t s   w i t h   i t s   e i g h t   n e i g h b o u r s ,   w h i c h   a r e   t h e   c e l l s   t h a t   a r e 
 h o r i z o n t a l l y ,   v e r t i c a l l y ,   o r   d i a g o n a l l y   a d j a c e n t .   A t   e a c h   s t e p   i n   t i m e ,   t h e 
 f o l l o w i n g   t r a n s i t i o n s   o c c u r : 
 
         A n y   l i v e   c e l l   w i t h   f e w e r   t h a n   t w o   l i v e   n e i g h b o u r s   d i e s ,   a s   i f   c a u s e d   b y 
             u n d e r - p o p u l a t i o n . 
         A n y   l i v e   c e l l   w i t h   t w o   o r   t h r e e   l i v e   n e i g h b o u r s   l i v e s   o n   t o   t h e   n e x t 
             g e n e r a t i o n . 
         A n y   l i v e   c e l l   w i t h   m o r e   t h a n   t h r e e   l i v e   n e i g h b o u r s   d i e s ,   a s   i f   b y 
             o v e r - p o p u l a t i o n . 
         A n y   d e a d   c e l l   w i t h   e x a c t l y   t h r e e   l i v e   n e i g h b o u r s   b e c o m e s   a   l i v e   c e l l ,   a s   i f 
             b y   r e p r o d u c t i o n . 
 
 
 T h e   i n i t i a l   p a t t e r n   c o n s t i t u t e s   t h e   s e e d   o f   t h e   s y s t e m .   T h e   f i r s t   g e n e r a t i o n   i s 
 c r e a t e d   b y   a p p l y i n g   t h e   a b o v e   r u l e s   s i m u l t a n e o u s l y   t o   e v e r y   c e l l   i n   t h e 
 s e e d  b i r t h s   a n d   d e a t h s   o c c u r   s i m u l t a n e o u s l y ,   a n d   t h e   d i s c r e t e   m o m e n t   a t   w h i c h 
 t h i s   h a p p e n s   i s   s o m e t i m e s   c a l l e d   a   t i c k   ( i n   o t h e r   w o r d s ,   e a c h   g e n e r a t i o n   i s   a 
 p u r e   f u n c t i o n   o f   t h e   p r e c e d i n g   o n e ) .   T h e   r u l e s   c o n t i n u e   t o   b e   a p p l i e d 
 r e p e a t e d l y   t o   c r e a t e   f u r t h e r   g e n e r a t i o n s . 
 W i k i p e d i a   * / 
 
 - -   F e a t u r e s   - - 
 T h i s   g a m e   a l l o w s   u s e r   t o   m o d i f y   c l a s s i c   r u l e s   t o   c r e a t e   c u s t o m   " g a m e   o f   l i f e " , 
 a n d   s e e   h o w   c h a n g i n g   r u l e s   a f f e c t s   t h e   g a m e .   A d d i t i o n a l l y   i t   i s   p o s s i b l e 
 t o   p a u s e   c u r r e n t   g a m e   t o   e x a m i n e   t h e   g r i d   c l o s e l y .   G a m e   a l s o   a l l o w s   n a v i g a t i n g 
 o n   t h e   g r i d   u s i n g   c o n t r o l s .   O t h e r   f e a t u r e s   i n c l u d e   c h a n g i n g   t h e   a p p e a r a n c e   o f 
 t h e   g a m e . 
 
 - -   I n s t a l l a t i o n   - - 
 
 I n s t a l l   d e p e n d e n c i e s   ( U b u n t u ) : 
 
     $   s u d o   a p t - g e t   i n s t a l l   l i b g t k - 3 - d e v   l i b g l i b 2 . 0 - d e v   f r e e g l u t 3 - d e v 
 
 C l o n e   t h e   r e p o s i t o r y   b y   u s i n g   G i t : 
 
     $   g i t   c l o n e   h t t p s : / / g i t h u b . c o m / j k u r r a / g a m e o f l i f e 
 
 T o   b u i l d   t h e   g a m e ,   r u n   m a k e . 
 
 - -   O t h e r   i n f o r m a t i o n   - - 
 
 T h i s   s o f t w a r e   i n c l u d e s   j s m n   l i b r a r y ,   w h i c h   c a n   b e   f o u n d   h e r e : 
     h t t p s : / / g i t h u b . c o m / z s e r g e / j s m n 
