using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _015_게임구조생각
{
    internal class ObservableProperty<T> where T : struct
    {
        private T _value;
        public T Value
        {
            get => _value;
            set
            {
                _value = value;
                OnValueChanged?.Invoke(_value);
            }
        }

        public event Action<T> OnValueChanged;

        public ObservableProperty(T initialValue = default)
        {
            _value = initialValue;
        }

        public void AddListener(Action<T> listener)
        {
            OnValueChanged += listener;
        }
        public void RemoveListener(Action<T> listener)
        {
            OnValueChanged -= listener;
        }

        public void RemoveAllListeners()
        {
            OnValueChanged = null;
        }
    }
}
