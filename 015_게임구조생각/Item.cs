using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _015_게임구조생각
{
    internal abstract class Item : BaseObject
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public abstract void Use();

        //PrintInfo


    }
}
