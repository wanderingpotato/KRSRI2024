class Kamera
{
private:
    Pixy2 pixy;
    int m_index;
    
public:
    Kamera() {}

    void init()
    {
        // Inisialiasai kamera
        pixy.init();
    }

    void getIndex(){
      // if(pixy.ccc.numBlocks==1){
      //   return pixy.ccc.blocks[0].m_index;
      // }else{
        int index=0;
        pixy.ccc.getBlocks();
        if (pixy.ccc.blocks)
        {
          for(int i=0;i<pixy.ccc.numBlocks;i++){
          // ||(pixy.ccc.blocks[i].m_width<pixy.ccc.blocks[i+1].m_width)||
            if((pixy.ccc.blocks[index].m_width<pixy.ccc.blocks[i].m_width)){
              index=i;
            }
          }
        }
        m_index=pixy.ccc.blocks[index].m_index;;
        Serial3.print(m_index);
      // }
      
    }
    int getKorban()
    {
        pixy.ccc.getBlocks();
        if (pixy.ccc.blocks)
        {
            for (int i = 0; i < pixy.ccc.numBlocks; i++)
            {
                if(pixy.ccc.blocks[i].m_index==m_index){
                  return i;
                }
                
            }
        }

        return -1;
    }

    int getWidth()
    {
        pixy.ccc.getBlocks();
        if (pixy.ccc.blocks)
        {
            for (int i = 0; i < pixy.ccc.numBlocks; i++)
            {
                if(pixy.ccc.blocks[i].m_index==m_index){
                  return pixy.ccc.blocks[i].m_width;
                }
                
            }
        }
    }

    int getHeight()
    {
        pixy.ccc.getBlocks();
        if (pixy.ccc.blocks)
        {
            for (int i = 0; i < pixy.ccc.numBlocks; i++)
            {
                if(pixy.ccc.blocks[i].m_index==m_index){
                  return pixy.ccc.blocks[i].m_height;
                }
                
            }
        }
    }

    int getX()
    {
        pixy.ccc.getBlocks();
        if (pixy.ccc.blocks)
        {
            for (int i = 0; i < pixy.ccc.numBlocks; i++)
            {
                if(pixy.ccc.blocks[i].m_index==m_index){
                  return pixy.ccc.blocks[i].m_x;
                }
                
            }
        }
    }

    int getY()
    {
        pixy.ccc.getBlocks();
        if (pixy.ccc.blocks)
        {
            for (int i = 0; i < pixy.ccc.numBlocks; i++)
            {
                if(pixy.ccc.blocks[i].m_index==m_index){
                  return pixy.ccc.blocks[i].m_y;
                }
                
            }
        }
    }

    void kameraPrintLocation()
    {
        Serial3.print("X : ");
        Serial3.print(getX());
        Serial3.print(" Y : ");
        Serial3.print(getY());
        Serial3.print(" W : ");
        int width = getWidth();
        int height = getHeight();
        Serial3.print(width);
        Serial3.print(" H : ");
        Serial3.print(height);
        Serial3.print(" W-H : ");
        Serial3.println(width - height);
    }

    void test(){
      int i;
        pixy.ccc.getBlocks();
  
        // If there are detect blocks, print them!
        if (pixy.ccc.numBlocks)
        {
          Serial3.print("Detected ");
          Serial3.println(pixy.ccc.numBlocks);
          for (i=0; i<pixy.ccc.numBlocks; i++)
          {
            Serial3.print("  block ");
            Serial3.print(i);
            Serial3.print(": Index :");
            Serial3.print(pixy.ccc.blocks[i].m_index);
            Serial3.print(",X : ");
            Serial3.print(pixy.ccc.blocks[i].m_x);
            Serial3.print(",WITDH : ");
            Serial3.print(pixy.ccc.blocks[i].m_width);
            Serial3.print(",HEIGHT : ");
            Serial3.print(pixy.ccc.blocks[i].m_height);
          }
        }  
    }

};
